#include "vdp_rend.h"
#include "blit.h"
void
Blit_Scale2x (unsigned char *Dest, int pitch, int x, int y, int offset) 
{
  
  
  
  
    // A B C
    // D E F
    // G H I
  
  
  
  
  
  
  
    
    {
      
      
      
      
	
	{
	  
	  E = F;
	  
	  
	  
	  
	  
	  
	  
	  
	    // E0
	    Dest[DstOffs] = E0;
	  
	  
	    // E1
	    Dest[DstOffs + 2] = E1;
	  
	  
	    // E2
	    Dest[DstOffs + pitch] = E2;
	  
	  
	    // E3
	    Dest[DstOffs + pitch + 2] = E3;
	  
	  
	
      
    


