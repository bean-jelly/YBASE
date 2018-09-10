#include "Thread.h"
#include <boost/weak_ptr.hpp>
#include <unistd.h>         //unix类系统定义符号常量的头文件，也包含了read(),write(),geepid(),sleep(),fork()等
#include <sys/prctl.h>      //进程相关
#include <sys/syscall.h>    //syscall()执行一个系统调用，根据指定的参数number和所有系统调用的汇编语言接口来确定调用哪个系统调用。
#include <sys/types.h>      //unix/Linux系统的基本系统数据类型的头文件，含有size_t，time_t，pid_t等类型
#include <linux/unistd.h>   

/*
进程pid: getpid()                 
线程tid: pthread_self()         //进程内唯一，但是在不同进程则不唯一。
线程pid: syscall(SYS_gettid)    //系统内是唯一的
*/

namespace YBASE
{
     namespace CurrentThread
    {
        pid_t tid();
        const char* name();
        bool isMainThread();
        __thread const char* t_threadName = "unknown";
    }

    //缓存线程的真实唯一ID
    __thread pid_t t_cachedTid = 0;

    pid_t gettid()
    {
        return static_cast<pid_t>(::syscall(SYS_gettid));
    }

    //parent fork创建了子进程以后，但在fork返回之前在父进程的进程环境中调用的
    void afterFork()
    {
        t_cachedTid = gettid();
        YBASE::CurrentThread::t_threadName = "main";
    }

    class ThreadNameInitializer
    {
    public:
        ThreadNameInitializer(){
            YBASE::CurrentThread::t_threadName = "main";
            /*
            pthread_atfork(void (*prepare)(void），void (*parent)(void）, void(*child)(void))
            prepare在父进程fork创建子进程之前调用，这里可以获取父进程定义的所有锁；
            child fork返回之前在子进程环境中调用，在这里unlock prepare获得的锁；
            parent fork创建了子进程以后，但在fork返回之前在父进程的进程环境中调用的，在这里对prepare获得的锁进行解锁；
            */
            pthread_atfork(NULL, NULL, &afterFork);
        }
    };

    ThreadNameInitializer init;

    struct ThreadData
    {
        typedef YBASE::Thread::ThreadFunc ThreadFunc;
        ThreadFunc func_;
        std::string name_;
        boost::weak_ptr<pid_t> wkTid_;

        ThreadData(const ThreadFunc& func,
                   const std::string& name,
                   const boost::shared_ptr<pid_t>& tid)
            :func_(func),
             name_(name),
             wkTid_(tid){}

        void runInThread()
        {
            pid_t tid = YBASE::CurrentThread::tid();
            //lock()获取shared_ptr<pid_t>
            boost::shared_ptr<pid_t> ptid = wkTid_.lock();

            if(ptid)
            {
                *ptid = tid;
                ptid.reset();
            }

            YBASE::CurrentThread::t_threadName = name_.empty() ? "YThread" : name_.c_str();
            //设置进程名称
            ::prctl(PR_SET_NAME, YBASE::CurrentThread::t_threadName);
            YBASE::CurrentThread::t_threadName = "finished";
        }
    };

    void* startThread(void* obj)
    {
        ThreadData* data = static_cast<ThreadData*>(obj);
        data->runInThread();
        delete data;
        return NULL;
    }
}

using namespace YBASE;

pid_t CurrentThread::tid()
{
    if(t_cachedTid == 0)
    {
        t_cachedTid = gettid();
    }
    return t_cachedTid;
}

const char* CurrentThread::name()
{
    return t_threadName;
}

bool CurrentThread::isMainThread()
{
    return tid() == ::getpid();
}

AtomicInt32 Thread::numCreated_;

Thread::Thread(const ThreadFunc& func, const std::string& n)
:started_(false),
 joined_(false),
 pthreadId_(0),
 tid_(new pid_t(0)),
 func_(func),
 name_(n)
{
    numCreate_.increment();
}

Thread::~Thread()
{
    if(started_ && !joined_)
    {
        pthread_detach(pthreadId_);
    }
}

void Thread::start()
{
    assert(!started_);
    started_ = true;

    ThreadData* data = new ThreadData(func_, name_, tid_);
    if(pthread_create(&pthreadId_, NULL, &startThread, data))
    {
        started_ = false;
        delete data;
        abort();
    }
}

void Thread::join()
{
    assert(started_);
    assert(!joined_);
    joined_ = true;
    pthread_join(pthreadId_, NULL);
}
