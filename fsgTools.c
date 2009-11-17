/*
Bastian Ruppert
*/

#include <defs.h>
#include "fsgGlobals.h"
#include "fsgTools.h"

static Uint32 fsgToolsGetPixel(SDL_Surface *surf, int x, int y)
{
	//This function returns pixels color
	int bpp = surf->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surf->pixels + y * surf->pitch + x * bpp;
	
	switch (bpp)
	{
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;
		
		case 4:
			return *(Uint32 *)p;
		
		default:
			return 0;
	}
}

/*! \brief Addiert auf die rgb-Werte den Offset drauf und gibt Uint32 MapRGB zurück
 *
 */
static Uint32 fsgToolsBecloudColor(SDL_PixelFormat * format,Uint8 *r,Uint8 *g, Uint8 * b, unsigned int offset){
  Uint8 tr,tg,tb;

  tr=*r;
  tg=*g;
  tb=*b;
  
  if(tr<(255-offset)){
      tr+=offset;
    }else{
      tr=255;
    }
  if(tg<(255-offset)){
	tg+=offset;
  }else{
    tg=255;
  }
  if(tb<(255-offset)){
    tb+=offset;
  }else{
    tb=255;
  }
  return SDL_MapRGB(format,tr,tg,tb); 
}
/*! \brief Subtrahiert von den rgb-Werten den Offset drauf und gibt Uint32 MapRGB zurück
 *
 */
static Uint32 fsgToolsBrightenColor(SDL_PixelFormat * format,Uint8 *r,Uint8 *g, Uint8 * b, unsigned int offset){
  Uint8 tr,tg,tb;

  tr=*r;
  tg=*g;
  tb=*b;
  
  if(tr>(offset)){
      tr-=offset;
    }else{
      tr=0;
    }
  if(tg>(offset)){
	tg-=offset;
  }else{
    tg=0;
  }
  if(tb>(offset)){
    tb-=offset;
  }else{
    tb=0;
  }
  return SDL_MapRGB(format,tr,tg,tb); 
}

/*! \brief Liefert aus dem Uint32 "ColorKey" die rgb-Werte
 *
 */
static int fsgToolGetRGB(Uint32 Color,Uint8 * pr,Uint8 * pg,Uint8 * pb)
{
  SDL_Surface * tmpSurface;

  SDL_PixelFormat * format = SDL_GetVideoSurface()->format;
  ec_null(tmpSurface=SDL_CreateRGBSurface(SDL_SWSURFACE,\
				  2,			\
				  2,			\
				  FSGDEFAULTCOLORDEPTH,	\
				  format->Rmask,	\
				  format->Gmask,	\
				  format->Bmask,	\
					  format->Amask) ) 

    ec_neg1( SDL_FillRect(tmpSurface,0,Color) )

  Uint32 thePixel = fsgToolsGetPixel(tmpSurface,0,0);
  SDL_FreeSurface(tmpSurface);
  SDL_GetRGB(thePixel,format,pr,pg,pb);//Die rgb-Werte des Rahmens sind nun endlich bekannt
  return 0;
  EC_CLEANUP_BGN
    SDL_FreeSurface(tmpSurface);
    return -1;
  EC_CLEANUP_END
}

static int fsgToolRenderBorder3D(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color,int boolUp)
{
  SDL_Rect r;
  Uint8 rot;
  Uint8 gruen;
  Uint8 blau;
 
  ec_neg1( fsgToolGetRGB(Color,&rot,&gruen,&blau) )
  
  Uint32 bright = fsgToolsBecloudColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,30);//hell
  Uint32 brighter = fsgToolsBecloudColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,60);//heller
  Uint32 dark = fsgToolsBrightenColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,30);//dunkel
  Uint32 darker = fsgToolsBrightenColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,60);//dunkler
  
  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = 2;
  r.h = PosDim->h;
  if(boolUp)
    {
    ec_neg1(SDL_FillRect(target,&r,bright) )//Border Innen Links
    }
  else
    { 
     ec_neg1(SDL_FillRect(target,&r,dark) )//Border Innen Links
    }
  
  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = PosDim->w;
  r.h = 2;
  if(boolUp)
    {
      ec_neg1(SDL_FillRect(target,&r,bright) )//Border Innen Oben
    }
  else
    {
    ec_neg1(SDL_FillRect(target,&r,dark) )
    }
  
  r.x = PosDim->w-2+PosDim->x;
  r.y = PosDim->y;
  r.w = 2;
  r.h = PosDim->h;
  if(boolUp)
    {        
     ec_neg1(SDL_FillRect(target,&r,dark))//Border Innen Rechts
    }
  else
    {
     ec_neg1(SDL_FillRect(target,&r,bright))
    }

  r.x = PosDim->x;
  r.y = PosDim->h-2+PosDim->y;
  r.w = PosDim->w;
  r.h = 2; 
  if(boolUp)
    {
     ec_neg1(SDL_FillRect(target,&r,dark))//Border Innen Unten
    }
  else
    {
     ec_neg1(SDL_FillRect(target,&r,bright))
    }

  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = 1;
  r.h = PosDim->h;
  if(boolUp)
    {
     ec_neg1(SDL_FillRect(target,&r,brighter))//Border Außen Links
    }
  else
    {
     ec_neg1(SDL_FillRect(target,&r,darker))
    }

  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = PosDim->w;
  r.h = 1;
  if(boolUp){
    if(SDL_FillRect(target,&r,brighter))//Border Außen Oben
      return -1;
  }else{
    if(SDL_FillRect(target,&r,darker))
      return -1;   
  }
  
  r.x = PosDim->w-1+PosDim->x;
  r.y = PosDim->y;
  r.w = 1;
  r.h = PosDim->h;
  if(boolUp)
    {        
      ec_neg1(SDL_FillRect(target,&r,darker))//Border Außen Rechts
    }
  else
    {
     ec_neg1(SDL_FillRect(target,&r,brighter))
    }
  
  r.x = PosDim->x;
  r.y = PosDim->h-1+PosDim->y;
  r.w = PosDim->w;
  r.h = 1; 
  if(boolUp)
    {
     ec_neg1(SDL_FillRect(target,&r,darker))//Border Außen Unten
    }
  else
    {
     ec_neg1(SDL_FillRect(target,&r,brighter))
    }
  
  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

extern int fsgToolRenderBorderFrame(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color)
{
  SDL_Rect r;
  Uint8 rot;
  Uint8 gruen;
  Uint8 blau;
  int boolUp = 0;
 
  ec_neg1(fsgToolGetRGB(Color,&rot,&gruen,&blau) )
  
  Uint32 bright = fsgToolsBecloudColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,30);//hell
  //Uint32 brighter = fsgToolsBecloudColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,60);//heller
  Uint32 dark = fsgToolsBrightenColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,30);//dunkel
  //Uint32 darker = fsgToolsBrightenColor(SDL_GetVideoSurface()->format,&rot,&gruen,&blau,60);//dunkler
  
  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = 2;
  r.h = PosDim->h;
  if(boolUp)
  {
    ec_neg1(SDL_FillRect(target,&r,dark))//Border Innen Links
  }else{
     ec_neg1(SDL_FillRect(target,&r,bright))//Border Innen Links
  }
  
  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = PosDim->w;
  r.h = 2;
  if(boolUp){
    ec_neg1(SDL_FillRect(target,&r,dark))//Border Innen Oben
  }else{
    ec_neg1(SDL_FillRect(target,&r,bright))
  }
  
  r.x = PosDim->w-2+PosDim->x;
  r.y = PosDim->y;
  r.w = 2;
  r.h = PosDim->h;
  if(boolUp){        
    ec_neg1(SDL_FillRect(target,&r,bright))//Border Innen Rechts
  }else{
    ec_neg1(SDL_FillRect(target,&r,dark))
  }

  r.x = PosDim->x;
  r.y = PosDim->h-2+PosDim->y;
  r.w = PosDim->w;
  r.h = 2; 
  if(boolUp){
    ec_neg1(SDL_FillRect(target,&r,bright))//Border Innen Unten
  }else{
    ec_neg1(SDL_FillRect(target,&r,dark))
  }

  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = 1;
  r.h = PosDim->h;
  if(boolUp){
    if(SDL_FillRect(target,&r,bright))//Border Außen Links
      return -1; 
  }else{
    if(SDL_FillRect(target,&r,dark))
      return -1;   
  }

  r.x = PosDim->x;
  r.y = PosDim->y;
  r.w = PosDim->w;
  r.h = 1;
  if(boolUp){
    ec_neg1(SDL_FillRect(target,&r,bright))//Border Außen Oben
  }else{
    ec_neg1(SDL_FillRect(target,&r,dark))
  }
  
  r.x = PosDim->w-1+PosDim->x;
  r.y = PosDim->y;
  r.w = 1;
  r.h = PosDim->h;
  if(boolUp){        
    ec_neg1(SDL_FillRect(target,&r,dark))//Border Außen Rechts
  }else{
    ec_neg1(SDL_FillRect(target,&r,bright))
  }
  
  r.x = PosDim->x;
  r.y = PosDim->h-1+PosDim->y;
  r.w = PosDim->w;
  r.h = 1; 
  if(boolUp){
    ec_neg1(SDL_FillRect(target,&r,dark))//Border Außen Unten
  }else{
    ec_neg1(SDL_FillRect(target,&r,bright))
  }
  return 0;   
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

extern int fsgToolRenderBorderUp(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color)
{
  return fsgToolRenderBorder3D(target,PosDim,Color,1);
}

extern int fsgToolRenderBorderDown(SDL_Surface * target,SDL_Rect * PosDim,Uint32 Color)
{
  return fsgToolRenderBorder3D(target,PosDim,Color,0);
}

int fsgToolRenderBorder(SDL_Surface * target,\
		       SDL_Rect * PosDim,\
		       int Breite,\
		       Uint32 Color)
{
  SDL_Rect r;
  r.x = PosDim->x;
  r.y = PosDim->y;
  //r.w = PosDim->w;
  r.h = PosDim->h;
  
  r.w = Breite;
  ec_neg1(SDL_FillRect(target,&r,Color))//Border Left

  r.x = PosDim->w-Breite+PosDim->x;
  ec_neg1(SDL_FillRect(target,&r,Color))//Border right

  r.x = PosDim->x;
  r.w = PosDim->w;
  r.h = Breite;
  ec_neg1(SDL_FillRect(target,&r,Color))//Border top

  r.y = PosDim->h-Breite+PosDim->y;
  ec_neg1(SDL_FillRect(target,&r,Color))//Border bottom

  return 0;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}

int fsgToolBlankSurface(SDL_Surface * s, Uint32 color){
  return SDL_FillRect(s,0,color);
}

int fsgToolsBlitText(SDL_Surface * tarSurface,SDL_Rect * posdim,TTF_Font * pFont,SDL_Color * pFontColor,const char * text)
{
  SDL_Surface * tmp;
  SDL_Rect des,src;
  //Position der Schrift berechnen
  int half,h_half;
  int h_mitte;
  int mitte;
  int ret = 0;

  if(pFont==0){
    return 0; 
  }
  if(pFontColor==0){
    return 0;
  }
  if(text==0){
    return 0;
  }
  ec_null(tmp = TTF_RenderText_Blended(pFont,text,*pFontColor) )

  h_mitte = (int)posdim->h/2;
  mitte = (int)posdim->w/2;
  if(posdim->w>=tmp->w)
    {
      half = tmp->w/2;
    }
  else
    {
      half = posdim->w/2;
    }
  if(posdim->h>=tmp->h)
    {
      h_half = tmp->h/2;
    }
  else
    {
      h_half = posdim->h/2;
    }
  half = (Sint16)(mitte-half);
  h_half = (Sint16)(h_mitte-h_half);
  des.x=posdim->x+half;
  des.y=posdim->y+h_half;//0;
  des.w=posdim->w;
  des.h=posdim->h; 
  src.x=0;//b->PositionDimension.x;//0;
  src.y=0;//b->PositionDimension.y;//0;
  src.w=posdim->w;
  src.h=posdim->h;
  ret = SDL_BlitSurface(tmp,&src,tarSurface,&des);
  SDL_FreeSurface(tmp);
  return ret;
  EC_CLEANUP_BGN
    return -1;
  EC_CLEANUP_END
}
