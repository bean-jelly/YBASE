 # i n c l u d e " t h r e a d p o o l . h "  
 # i n c l u d e < i o s t r e a m >  
  
 v o i d   f u n 1 ( i n t   s l p )  
 {  
 	 p r i n t f ( "   h e l l o ,   f u n 1   % d \ n " ,   s t d : : t h i s _ t h r e a d : : g e t _ i d ( ) ) ;  
 	 i f   ( s l p   >   0 )  
 	 {  
 	 	 p r i n t f ( " = = = = = = = = = =   f u n 1   s l e e p   % d   = = = = = = = = = = =   % d \ n " ,   s l p ,   s t d : : t h i s _ t h r e a d : : g e t _ i d ( ) ) ;  
 	 	 s t d : : t h i s _ t h r e a d : : s l e e p _ f o r ( s t d : : c h r o n o : : m i l l i s e c o n d s ( s l p ) ) ;  
 	 }  
 }  
  
 s t r u c t   g f u n  
 {  
 	 i n t   o p e r a t o r ( ) ( i n t   n )  
 	 {  
 	 	 p r i n t f ( " % d   h e l l o ,   g f u n   !     % d \ n " ,   n ,   s t d : : t h i s _ t h r e a d : : g e t _ i d ( ) ) ;  
 	 	 r e t u r n   4 2 ;  
 	 }  
 } ;  
  
 c l a s s   A  
 {  
 	 p u b l i c :  
 	 	 s t a t i c   i n t   A f u n ( i n t   n   =   0 )  
 	 	 {  
 	 	 	 s t d : : c o u t   < <   n   < <   " 	 h e l l o ,   A f u n   !   "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 	 r e t u r n   n ;  
 	 	 }  
  
 	 	 s t a t i c   s t d : : s t r i n g   B f u n ( i n t   n ,   s t d : : s t r i n g   s t r ,   c h a r   c )  
 	 	 {  
 	 	 	 s t d : : c o u t   < <   n   < <   "   h e l l o ,   B f u n   !   "   < <   s t r . c _ s t r ( )   < <   "   "   < <   ( i n t ) c   < <   "   "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 	 r e t u r n   s t r ;  
 	 	 }  
 } ;  
  
 i n t   m a i n ( )  
 {  
 	 t r y {  
 	 	 s t d : : t h r e a d p o o l   e x e c u t o r { 5 0 } ;  
 	 	 A   a ;  
 	 	 s t d : : f u t u r e < v o i d >   f f   =   e x e c u t o r . c o m m i t ( f u n 1 ,   0 ) ;  
 	 	 s t d : : f u t u r e < i n t >   f g   =   e x e c u t o r . c o m m i t ( g f u n { } ,   0 ) ;  
 	 	 s t d : : f u t u r e < i n t >   g g   =   e x e c u t o r . c o m m i t ( a . A f u n ,   9 9 9 9 ) ;  
 	 	 s t d : : f u t u r e < s t d : : s t r i n g >   g h   =   e x e c u t o r . c o m m i t ( A : : B f u n ,   9 9 9 8 ,   " m u l t   a r g s " ,   1 2 3 ) ;  
 	 	 s t d : : f u t u r e < s t d : : s t r i n g >   f h   =   e x e c u t o r . c o m m i t (  
 	 	 	 	 [ ] ( ) - > s t d : : s t r i n g  
 	 	 	 	 {  
 	 	 	 	 s t d : : c o u t   < <   " h e l l o ,   f h !   "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 	 	 r e t u r n   " h e l l o ,   f h   r e t   ! " ;  
 	 	 	 	 } ) ;  
 	 	 s t d : : c o u t   < <   " = = = = = = = = = = = = = = = = =   s l e e p   = = = = = = = = = = = = = = = = = = "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 s t d : : t h i s _ t h r e a d : : s l e e p _ f o r ( s t d : : c h r o n o : : m i c r o s e c o n d s ( 9 0 0 ) ) ;  
 	 	 f o r ( i n t   i   =   0 ;   i   <   5 0 ;   i + + )  
 	 	 {  
 	 	 	 e x e c u t o r . c o m m i t ( f u n 1 ,   i * 1 0 0 ) ;  
 	 	 }  
 	 	 s t d : : c o u t   < <   " = = = = = = = = = = = = = = = = =   c o m m i t   a l l   = = = = = = = = = = = = = = = = = = = = "   < <  
 	 	 	 s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   " i d l s i z e = "   < <   e x e c u t o r . i d l C o u n t ( )   < <   s t d : : e n d l ;  
 	 	 s t d : : c o u t   < <   " = = = = = = = = = = = = = = = = =   s l e e p   = = = = = = = = = = = = = = = = = = "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 s t d : : t h i s _ t h r e a d : : s l e e p _ f o r ( s t d : : c h r o n o : : s e c o n d s ( 3 ) ) ;  
 	 	 f f . g e t ( ) ;   / /�u( . g e t ( )��S֏�V�P<O{I_�~�zbg�L[�b���S֏�V�P<  
 	 	 s t d : : c o u t   < <   f g . g e t ( )   < <   "   "   < <   f h . g e t ( ) . c _ s t r ( )   < <   "   "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 s t d : : c o u t   < <   " = = = = = = = = = = = = = = = = =   s l e e p   = = = = = = = = = = = = = = = = = = "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 s t d : : t h i s _ t h r e a d : : s l e e p _ f o r ( s t d : : c h r o n o : : s e c o n d s ( 3 ) ) ;  
  
 	 	 s t d : : c o u t   < <   " = = = = = = = = = = = = = = = = =   f u n 1 ,   5 5   = = = = = = = = = = = = = = = = = = = = "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
 	 	 e x e c u t o r . c o m m i t ( f u n 1 ,   5 5 ) . g e t ( ) ;  
 	 	 s t d : : c o u t   < <   " e n d . . . "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
  
 	 	 s t d : : t h r e a d p o o l   p o o l ( 4 ) ;  
 	 	 s t d : : v e c t o r < s t d : : f u t u r e < i n t >   >   r e s u l t s ;  
  
 	 	 f o r ( i n t   i   =   0 ;   i   <   8 ;   + + i )  
 	 	 {  
 	 	 	 r e s u l t s . e m p l a c e _ b a c k (  
 	 	 	 	 	 p o o l . c o m m i t ( [ i ] {  
 	 	 	 	 	 	 s t d : : c o u t   < <   " h e l l o   "   < <   i   < <   s t d : : e n d l ;  
 	 	 	 	 	 	 s t d : : t h i s _ t h r e a d : : s l e e p _ f o r ( s t d : : c h r o n o : : s e c o n d s ( 1 ) ) ;  
 	 	 	 	 	 	 s t d : : c o u t   < <   " w o r l d   "   < <   i   < <   s t d : : e n d l ;  
 	 	 	 	 	 	 r e t u r n   i * i ;  
 	 	 	 	 	 } )  
 	 	 	 	 ) ;  
 	 	 }  
 	 	 s t d : : c o u t   < <   " = = = = = = = = = = = = = = =   c o m m i t   a l l 2   = = = = = = = = = = = = = = = = = = "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   s t d : : e n d l ;  
  
 	 	 f o r ( a u t o   & &   r e s u l t   :   r e s u l t s )  
 	 	 {  
 	 	 	 s t d : : c o u t   < <   r e s u l t . g e t ( )   < <   '   ' ;  
 	 	 }  
 	 	 s t d : : c o u t   < <   s t d : : e n d l ;  
 	 	 r e t u r n   0 ;  
 	 }  
 	 c a t c h ( s t d : : e x c e p t i o n &   e ) {  
 	 	 s t d : : c o u t   < <   " s o m e   u n h a p p y   h a p p e n e d . . .   "   < <   s t d : : t h i s _ t h r e a d : : g e t _ i d ( )   < <   e . w h a t ( )   < <   s t d : : e n d l ;  
 	 }  
 }  
