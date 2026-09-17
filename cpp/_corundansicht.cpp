#include "../hpp/_corundansicht.hpp"

//******************************************************************************************************************************************************************************************************
//                                                              T E X T U R A N S I C H T
//******************************************************************************************************************************************************************************************************
_texturansicht::_texturansicht(_hauptfenster*hf,_guifensterkartei*tw):_guifensterkarteiseite(L"Textur",tw){
                                hauptfenster=hf;
                                panwahl=0;
                                pdc=0;
                                #ifdef CORUND_MIT_OPENGL
                                 pdc=new _guikontext(this);
                                 grafik=new _grafikopengl((unsigned int)pdc->kontext(), 0,0,320,240);
                                #else
                                 grafik=new _grafikdirectx(handle(),false,false,0,0,320,240,0,0,0,0);
                                #endif
                                grafik->gemeinsamedaten(hauptfenster->ansicht[0]->grafik);
                                int  sbWidth = GetSystemMetrics(SM_CXVSCROLL); 
                                scrollbar = new _guiscrollbarvertikal(this); 
                                *scrollbar += new _guiort<_tg>(1, 0, false); 
                                *scrollbar += new _guiort<_tg>(-sbWidth, 0); 
                                *scrollbar += new _guigroesse<_tg>(0, 1, false); 
                                *scrollbar += new _guigroesse<_tg>(sbWidth, 0);  
                                scrollbar->zeigen();
                                *this += new _guiereignisSize<_texturansicht>(this, &_texturansicht::beigroesse);
                                *this += new _guiereignisPaint<_texturansicht>(this, &_texturansicht::zeichnen);
                                *this += new _guiereignisLeftButtonDown<_texturansicht>(this, &_texturansicht::beimauslinksein);
                                besitzerzeichnung(true);
                                zeigen();
                                                               
                                
};
_texturansicht::~_texturansicht(){
                                delete grafik;
                                deletesecure(pdc);
};
void _texturansicht::aktualisieren(){
                                if(hauptfenster->corundwelt){
                                 _textur<_tb>*lnt;
                                 if(hauptfenster->corundwelt->textur._listebasis<_textur<_tb> >::anfang(lnt)) panwahl=lnt;
                                 _tg ty=_tg(hauptfenster->corundwelt->textur._listebasis<_textur<_tb> >::anzahl())*grafik->groessex();
                                 scrollbar->bereich(0,ty);
                                // scrollbar->Pos(ty);
                                 scrollbar->skalieren();
                                 //neuzeichnen();
                                };
};
_textur<_tb>* _texturansicht::anwahl(){
                                return(panwahl);
};
void _texturansicht::beigroesse(_guiereignisdaten *ep){
                                _guirechteck<int> rect;
                                scrollbar->skalieren();
                                rect=scrollbar->WindowRect<int>();
                                int sbwidth=rect.rechts()-rect.links();
                                rect=ClientRect<int>();
                                grafik->aktivitaet(true);
                                grafik->groesse(rect.breite()-sbwidth,rect.hoehe());
};
void _texturansicht::beimauslinksein(_guiereignisdaten *ep){
                                if(hauptfenster->corundwelt){
                                 _textur<_tb>*t;
                                 _vektor2<_tg> mo(ep->maus.x,grafik->groessey()-ep->maus.y);
                                 _tg wx=grafik->groessex();
                                 _tg sp=scrollbar->ort();
                                 _tg wy=grafik->groessey()-wx;
                                 _vektor3<_tg> v(0,-wx,0);
                                 _vektor3<_tg> o[4];
                                 o[0].setzen(0,wy+sp,1);
                                 o[1].setzen(wx,wy+sp,1);
                                 o[2].setzen(wx,(wy+wx)+sp,1);
                                 o[3].setzen(0,(wy+wx)+sp,1);                                
                                 if(hauptfenster->corundwelt->textur.anfang(t)){
                                  do{
                                   if((o[0][1]>=-wx)&&(o[0][1]<=grafik->groessey())){
                                    if((mo[0]>=o[0][0])&&(mo[0]<=o[1][0])&&(mo[1]>=o[0][1])&&(mo[1]<=o[2][1])){
                                     panwahl=t;
                                     _polygon*pit;
                                     _netz*nit;
                                     bool repaint=false;
                                     
                                     _listenknoten<_netz>*lnnit;
                                     iterierenliste(&hauptfenster->anwahlnetzliste,lnnit,iterierenliste(lnnit->objekt(),pit,
                                      pit->textur(panwahl);
                                      repaint=true;
                                      hauptfenster->statusbar->text(2,L"Netztextur wurde geändert");
                                     ));
                                     if(hauptfenster->anwahlpolygonliste.erstes()){
                                      _listenknoten<_polygon>*p;
                                      iterierenliste((&hauptfenster->anwahlpolygonliste),p,p->objekt()->textur(panwahl));
                                      repaint=true;
                                      hauptfenster->statusbar->text(2,L"Polygontextur wurde geändert");
                                     };
                                     /*if(hauptfenster->corundwelt->welt->anfang(nit))do{
                                      if(nit->anfang(pit))do{
                                       if(pit->anwahl()!=0) {
                                        pit->textur(panwahl);
                                        
                                        hauptfenster->statusbar->text(2,L"Polygontextur wurde geändert");
                                        repaint=true;
                                       };
                                       
                                      }while(nit->naechstes(pit));
                                     }while(hauptfenster->corundwelt->welt->naechstes(nit));*/
                                     
                                     
                                     if(repaint){
                                      hauptfenster->ansicht[0]->neuzeichnen();
                                      hauptfenster->ansicht[1]->neuzeichnen();
                                      hauptfenster->ansicht[2]->neuzeichnen();
                                      hauptfenster->ansicht[3]->neuzeichnen();
                                     };
                                     neuzeichnen();
                                     return;
                                    };
                                   };
                                   for(int i=0;i<4;i++) o[i]+=v;
                                  }while(hauptfenster->corundwelt->textur.naechstes(t));
                                 };
                                };
};

void _texturansicht::zeichnen(_guiereignisdaten *ep){
                                grafik->aktivitaet(true);
                                if(grafik->szenebeginn()){
                                 grafik->validieren();                                
                                 grafik->anzeigebufferloeschfarbe(0,0,0,0);//glClearColor(0,0,0,0);
                                 grafik->anzeigebufferschreiben(true);//glColorMask(1,1,1,1);
                                 grafik->allebufferloeschen();
                                 grafik->orthonormal(0,grafik->groessex(), 0,grafik->groessey(), -100, 100);//glOrtho(0,grafik->groessex(), 0,grafik->groessey(), -100, 100);
                                 if(hauptfenster->corundwelt){
                                  _tg wx=grafik->groessex();
                                  _tg sp=scrollbar->ort();
                                  _textur<_tb>*t;
                                  _bild<_tb>*bild;
                                  _bild<_tb>*lmap;
                                  _bild<_tb>*smap;
                                  _vektor3<_tg> o[4];
                                  _vektor3<_tg> q[4];
                                  _vektor3<_tg> m;
                                  _vektor2<_tg> tk[4];
                                  _vektor4<_to> c(1,1,1,1);
                                  _vektor4<_to> ca(0,1,0,1);
                                  _vektor3<_tg> v(0,-wx,0);
                                  _tg wy=grafik->groessey()-wx;
                                  o[0].setzen(0,wy+sp,1);
                                  o[1].setzen(wx,wy+sp,1);
                                  o[2].setzen(wx,(wy+wx)+sp,1);
                                  o[3].setzen(0,(wy+wx)+sp,1);
                                  tk[0].setzen(0,0);
                                  tk[1].setzen(1,0);
                                  tk[2].setzen(1,1);
                                  tk[3].setzen(0,1);
                                  if(hauptfenster->corundwelt->textur.anfang(t)){
                                   do{
                                    if((o[0][1]>=-wx)&&(o[0][1]<=grafik->groessey())){
                                     grafik->ausschussflaeche(false);//glDisable(GL_CULL_FACE);
                                     grafik->beleuchtung(false);//glDisable(GL_LIGHTING);
                                     grafik->transparenz(false);//glDisable(GL_BLEND);
                                     grafik->tiefenbufferkondition(false);
                                     grafik->maske(false);
                                     bindentextur(grafik,t,bild,lmap,smap);
                                     if(bild){
                                      if(lmap){
                                       if(smap){//----------------- bitmap, lightmap und specularmap 
                                        grafik->zeichnen(o[0],o[1],o[2],c,c,c,tk[0],tk[1],tk[2],tk[0],tk[1],tk[2],tk[0],tk[1],tk[2]);
                                        grafik->zeichnen(o[0],o[2],o[3],c,c,c,tk[0],tk[2],tk[3],tk[0],tk[2],tk[3],tk[0],tk[2],tk[3]);
                                       }else{//-------------------nur bitmap und lightmap
                                        grafik->zeichnen(o[0],o[1],o[2],c,c,c,tk[0],tk[1],tk[2],tk[0],tk[1],tk[2]);
                                        grafik->zeichnen(o[0],o[2],o[3],c,c,c,tk[0],tk[2],tk[3],tk[0],tk[2],tk[3]);
                                       };
                                      }else{//-------------------nur bitmap
                                       grafik->zeichnen(o[0],o[1],o[2],c,c,c,tk[0],tk[1],tk[2]);
                                       grafik->zeichnen(o[0],o[2],o[3],c,c,c,tk[0],tk[2],tk[3]);
                                      };
                                     };
                                     if(panwahl==t){
                                      grafik->textur(false);
                                      grafik->zeichnen(o[0],o[1],ca,ca);
                                      grafik->zeichnen(o[1],o[2],ca,ca);
                                      grafik->zeichnen(o[2],o[3],ca,ca);
                                      grafik->zeichnen(o[3],o[0],ca,ca);
                                      m=o[0]+o[1]+o[2]+o[3];
                                      m*=0.25f;
                                      for(int i=0;i<4;i++) q[i]=o[i]+(m-o[i])*0.25;
                                      grafik->zeichnen(q[0],q[1],ca,ca);
                                      grafik->zeichnen(q[1],q[2],ca,ca);
                                      grafik->zeichnen(q[2],q[3],ca,ca);
                                      grafik->zeichnen(q[3],q[0],ca,ca);
                                      
                                      grafik->zeichnen(o[0],q[0],ca,ca);
                                      grafik->zeichnen(o[1],q[1],ca,ca);
                                      grafik->zeichnen(o[2],q[2],ca,ca);
                                      grafik->zeichnen(o[3],q[3],ca,ca);
                                     };
                                    };
                                    for(int i=0;i<4;i++) o[i]+=v;
                                   }while(hauptfenster->corundwelt->textur.naechstes(t));
                                  };
                                 };
                                 grafik->szeneende();
                                };
                                grafik->anzeigebufferumschalten();
};
void _texturansicht::bindentextur(_grafik*g,_textur<_tb>*tex,_bild<_tb>*&bild,_bild<_tb>*&lmap,_bild<_tb>*&smap){
                                bild=0;
                                lmap=0;
                                smap=0;
                                _textur<_tb>*ptextur=tex;
                                _listenknoten<_bild<_tb> >*lnbild;
                                _listenknoten<_bild<_tb> >*lnsmap;
                                if(ptextur){ 
                                 if(ptextur->bitmap()->anfang(lnbild)) {
                                  bild=lnbild->objekt();
                                  g->textureinheit(0);//glActiveTextureARB(GL_TEXTURE0_ARB);
                                  if(lmap==0) g->texturoperationmultiplikativ(); else g->texturoperationadditiv();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	                              g->textur(true);//glEnable(GL_TEXTURE_2D);
                                  g->bindenbild(bild); 
                                 };
                                 if(ptextur->specularmap()->anfang(lnsmap)) {
                                  smap=lnsmap->objekt();
                                  g->textureinheit(2);//glActiveTextureARB(GL_TEXTURE2_ARB);
                                  g->texturoperationadditiv();//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_ADD);
	                              g->textur(true);//glEnable(GL_TEXTURE_2D);
                                  g->bindenbild(smap); 
                                 };
                                 g->textur(true); 
                                } else g->textur(false);
};
//******************************************************************************************************************************************************************************************************
//                                                              S C H N I T T 
//******************************************************************************************************************************************************************************************************
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_polygon*o,_tg t){
                                init();
                                polygon=o;
                                l->einfuegenunredundant(this,t);
};
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_licht<_tg,_to>*o,_tg t){
                                init();
                                licht=o;
                                l->einfuegenunredundant(this,t);
};
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_corundknoten*o,_tg t){
                                init();
                                knoten=o;
                                l->einfuegenunredundant(this,t);
};
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_gravitation<_tg>*o,_tg t){
                                init();
                                gravitation=o;
                                l->einfuegenunredundant(this,t);
};
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_feldmagnetostatisch<_tg>*o,_tg t){
                                init();
                                feldmagnetostatisch=o;
                                l->einfuegenunredundant(this,t);
};
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_feldelektrostatisch<_tg>*o,_tg t){
                                init();
                                feldelektrostatisch=o;
                                l->einfuegenunredundant(this,t);
};
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_partikelquelle*o,_tg t){
                                init();
                                partikelquelle=o;
                                l->einfuegenunredundant(this,t);
};
_schnitt::_schnitt(_listesortiert<_schnitt,_tg>*l,_corundkugel*o,_tg t){
                                init();
                                kugel=o;
                                l->einfuegenunredundant(this,t);
};
void _schnitt::init(){
                                polygon=0;
                                licht=0;
                                gravitation=0;
                                feldelektrostatisch=0;
                                feldmagnetostatisch=0;
                                kugel=0;
                                knoten=0;
                                partikelquelle=0;
};
_schnitt::~_schnitt(){
};

//******************************************************************************************************************************************************************************************************
//                                                              A N S I C H T
//******************************************************************************************************************************************************************************************************
_ansicht::_ansicht(_hauptfenster*hf,_guifenster*dummy,const _zeichenkette<char>&n):_guifensterkind(dummy){
                                hauptfenster=hf;
                                name=n;
                                istxz=false;
                                istxy=false;
                                istyz=false;
                                sichtkopplung0=0;
                                sichtkopplung1=0;
                                farbe.setzen(7.0f/256.0f,0,51.0f/256.0f,1);
                                links=false;
                                rechts=false;
                                modus=0;
                                editionskopplung=0;
                                pdc=0;
                                #ifdef CORUND_MIT_OPENGL
                                 pdc=new _guikontext(this);
                                 grafik=new _grafikopengl((unsigned int)pdc->kontext(), 0,0,320,240);
                                #else
                                 grafik=new _grafikdirectx(handle(),false,false,0,0,320,240,0,0,0,0);
                                // grafik->fensterkontrolle(false);
                                #endif
                                
                                *this += new _guiereignisPaint<_ansicht>(this, &_ansicht::zeichnen);
                                *this += new _guiereignisSize<_ansicht>(this, &_ansicht::beigroesse);
                                *this += new _guiereignisLeftButtonDoubleClick<_ansicht>(this, &_ansicht::beimauslinksdoppelklick);
                                *this += new _guiereignisRightButtonDoubleClick<_ansicht>(this, &_ansicht::beimausrechtsdoppelklick);
                                *this += new _guiereignisLeftButtonDown<_ansicht>(this, &_ansicht::beimauslinksein);
                                *this += new _guiereignisLeftButtonUp<_ansicht>(this, &_ansicht::beimauslinksaus);
                                *this += new _guiereignisRightButtonDown<_ansicht>(this, &_ansicht::beimausrechtsein);
                                *this += new _guiereignisRightButtonUp<_ansicht>(this, &_ansicht::beimausrechtsaus);
                                *this += new _guiereignisMouseMove<_ansicht>(this, &_ansicht::beimausbewegung);
                                *this += new _guiereignisMouseWheel<_ansicht>(this, &_ansicht::beimausrad);
                                kamera=new _kamera<_tg>(hauptfenster);
                                kamera->vektorebene0(_vektor3<_tg>(0,-1,0),_vektor3<_tg>(1,0,0));
                                kamera->setzen(0,12,0);
                                menuvertex=new _guimenue(L"Bearbeiten");
                                *menuvertex += new _guimenueeintrag(L"&Vertexeigenschaften bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenvertex)); 
                                menupolygon=new _guimenue(L"Bearbeiten");
                                *menupolygon += new _guimenueeintrag(L"&Polygoneigenschaften bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenpolygon)); 
                                *menupolygon += new _guimenueeintrag(L"&Texturgeometrie bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenpolygontexturgeometrie)); 
                                *menupolygon += new _guimenueeintrag(L"&Polygon löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschenpolygon)); 
                                menunetz=new _guimenue(L"Bearbeiten");
                                *menunetz += new _guimenueeintrag(L"&Netz bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitennetz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz kopieren", new _guiereignisCommand<_ansicht>(this, &_ansicht::beikopierennetz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz invertieren", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiinvertieren)); 
                                *menunetz += new _guimenueeintrag(L"&Netz zum Raster verschieben", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiverschiebenraster)); 
                                *menunetz += new _guimenueeintrag(L"&Netz tauschen x <-> y", new _guiereignisCommand<_ansicht>(this, &_ansicht::beitauschenxy)); 
                                *menunetz += new _guimenueeintrag(L"&Netz tauschen x <-> z", new _guiereignisCommand<_ansicht>(this, &_ansicht::beitauschenxz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz tauschen y <-> z", new _guiereignisCommand<_ansicht>(this, &_ansicht::beitauschenyz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz spiegeln x", new _guiereignisCommand<_ansicht>(this, &_ansicht::beispiegelnx)); 
                                *menunetz += new _guimenueeintrag(L"&Netz spiegeln y", new _guiereignisCommand<_ansicht>(this, &_ansicht::beispiegelny)); 
                                *menunetz += new _guimenueeintrag(L"&Netz spiegeln z", new _guiereignisCommand<_ansicht>(this, &_ansicht::beispiegelnz)); 
                                *menunetz += new _guimenueeintrag(L"&Netze vereinigen ohne Schitt", new _guiereignisCommand<_ansicht>(this, &_ansicht::beivereinigungnetzohneschnitt)); 
                                *menunetz += new _guimenueeintrag(L"&Netz-=+Welt Intersektion", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiintersektionnetz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz-=-Welt Intersektion", new _guiereignisCommand<_ansicht>(this, &_ansicht::beideintersektionnetz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz+=+Netz Intersektion", new _guiereignisCommand<_ansicht>(this, &_ansicht::beivereinigungnetz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz+=+Welt Intersektion", new _guiereignisCommand<_ansicht>(this, &_ansicht::beivereinigungnetzwelt)); 
                                *menunetz += new _guimenueeintrag(L"&Netz/=+Welt Intersektion", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiteilungnetz)); 
                                *menunetz += new _guimenueeintrag(L"Netz Texturen neuskalieren", new _guiereignisCommand<_ansicht>(this, &_ansicht::beinetztexturneuskalieren)); 
                                *menunetz += new _guimenueeintrag(L"Netz komplanare Flächen nicht zeichnen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beinetzkomplanarenichtzeichnen)); 
                                *menunetz += new _guimenueeintrag(L"Netz komplanare Flächen nicht kollidieren", new _guiereignisCommand<_ansicht>(this, &_ansicht::beinetzkomplanarenichtkollidieren)); 
                                *menunetz += new _guimenueeintrag(L"Netz komplanare Flächen schattieren keine Lightmap", new _guiereignisCommand<_ansicht>(this, &_ansicht::beinetzkomplanarekeinschattenwurflightmap)); 
                                *menunetz += new _guimenueeintrag(L"&Fraktal abbilden", new _guiereignisCommand<_ansicht>(this, &_ansicht::beifraktal)); 
                                *menunetz += new _guimenueeintrag(L"&Biegen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibiegen)); 
                                *menunetz += new _guimenueeintrag(L"&Rotieren", new _guiereignisCommand<_ansicht>(this, &_ansicht::beirotieren)); 
                                *menunetz += new _guimenueeintrag(L"&Verdrehen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiverdrehen)); 
                                *menunetz += new _guimenueeintrag(L"&Skalieren abs. *2", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiskalierenmul2)); 
                                *menunetz += new _guimenueeintrag(L"&Skalieren abs. /2", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiskalierendiv2)); 
                                *menunetz += new _guimenueeintrag(L"&Netz isoliert speichern", new _guiereignisCommand<_ansicht>(this, &_ansicht::beispeichernnetz)); 
                                *menunetz += new _guimenueeintrag(L"&Netz löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschennetz)); 
                                
                                menulicht=new _guimenue(L"Bearbeiten");
                                *menulicht += new _guimenueeintrag(L"&Lichteigenschaften bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenlicht)); 
                                *menulicht += new _guimenueeintrag(L"&Licht kopieren", new _guiereignisCommand<_ansicht>(this, &_ansicht::beikopierenlicht)); 
                                *menulicht += new _guimenueeintrag(L"&Licht löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschenlicht)); 

                                menuknoten=new _guimenue(L"Bearbeiten");
                                *menuknoten += new _guimenueeintrag(L"&Knoteneigenschaften bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenknoten)); 
                                *menuknoten += new _guimenueeintrag(L"&Knoten löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschenknoten)); 

                                menugravitation=new _guimenue(L"Bearbeiten");
                                *menugravitation += new _guimenueeintrag(L"&Gravitationseigenschaften bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitengravitation)); 
                                *menugravitation += new _guimenueeintrag(L"&Gravitation löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschengravitation)); 

                                menufeldelektrostatisch=new _guimenue(L"Bearbeiten");
                                *menufeldelektrostatisch += new _guimenueeintrag(L"&Elektrostatisches Feld bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenfeldelektrostatisch)); 
                                *menufeldelektrostatisch += new _guimenueeintrag(L"&Elektrostatisches Feld löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschenfeldelektrostatisch)); 

                                menufeldmagnetostatisch=new _guimenue(L"Bearbeiten");
                                *menufeldmagnetostatisch += new _guimenueeintrag(L"&Magnetostatisches Feld bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenfeldmagnetostatisch)); 
                                *menufeldmagnetostatisch += new _guimenueeintrag(L"&Magnetostatisches Feld löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschenfeldmagnetostatisch)); 

                                menupartikelquelle=new _guimenue(L"Bearbeiten");
                                *menupartikelquelle += new _guimenueeintrag(L"&Partikelquelle Eigenschaften bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenpartikelquelle)); 
                                *menupartikelquelle += new _guimenueeintrag(L"&Partikelquelle kopieren", new _guiereignisCommand<_ansicht>(this, &_ansicht::beikopierenpartikelquelle)); 
                                *menupartikelquelle += new _guimenueeintrag(L"&Partikelquelle löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschenpartikelquelle)); 

                                menukugel=new _guimenue(L"Bearbeiten");
                                *menukugel += new _guimenueeintrag(L"&Kugeleigenschaften bearbeiten", new _guiereignisCommand<_ansicht>(this, &_ansicht::beibearbeitenkugel)); 
                                *menukugel += new _guimenueeintrag(L"&Kugel löschen", new _guiereignisCommand<_ansicht>(this, &_ansicht::beiloeschenkugel)); 
};
_ansicht::~_ansicht(){
                                delete kamera;
                                delete grafik;
                                deletesecure(pdc);
                                ls.loeschen();
};
void _ansicht::beigroesse(_guiereignisdaten *ep){
                                _guirechteck<int>  rect = ClientRect<int>();
                                grafik->aktivitaet(true);
                                grafik->groesse(rect.breite(),rect.hoehe());
};
void _ansicht::beimauslinksdoppelklick(_guiereignisdaten*ep){
                                if(hauptfenster->testmodus==false)
                                pruefenkollision(_vektor2<_tg>(ep->maus.x,ep->maus.y));
};
void _ansicht::beimausrechtsdoppelklick(_guiereignisdaten*){
};
void _ansicht::beimauslinksein(_guiereignisdaten *ep){
                                links=true;
                                altepos.setzen(ep->maus.x,ep->maus.y);
};
void _ansicht::beimauslinksaus(_guiereignisdaten *ep){
                                links=false;
                               // _win::_tastatur kb;
                               // if(kb.control()){
                                // pruefenkollision(_vektor2<_tg>(ep->maus.x,ep->maus.y));
                               // };
};
void _ansicht::beimausrechtsein(_guiereignisdaten *ep){
                                rechts=true;
                                altepos.setzen(ep->maus.x,ep->maus.y);
                               // pruefenkollision(_vektor2<_tg>(ep->maus.x,ep->maus.y));
};
void _ansicht::beimausrechtsaus(_guiereignisdaten *ep){
                                rechts=false;
                                if((!links)&&(hauptfenster->testmodus==false)){
                                 if(hauptfenster->anwahlvertexliste.erstes()){
                                  menuvertex->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                 if(hauptfenster->anwahlpolygonliste.erstes()){
                                  menupolygon->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                 if(hauptfenster->anwahlnetzliste.erstes()){
                                  menunetz->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                 if(hauptfenster->anwahllicht){
                                  menulicht->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                 if(hauptfenster->anwahlknoten){
                                  menuknoten->popup(this,ep->maus.x,ep->maus.y);
                                 };

                                 if(hauptfenster->anwahlgravitation){
                                  menugravitation->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                 if(hauptfenster->anwahlfeldelektrostatisch){
                                  menufeldelektrostatisch->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                 if(hauptfenster->anwahlfeldmagnetostatisch){
                                  menufeldmagnetostatisch->popup(this,ep->maus.x,ep->maus.y);
                                 };

                                 if(hauptfenster->anwahlpartikelquelle){
                                  menupartikelquelle->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                 if(hauptfenster->anwahlkugel){
                                  menukugel->popup(this,ep->maus.x,ep->maus.y);
                                 };
                                };
};
void _ansicht::beimausrad(_guiereignisdaten *){
};
void _ansicht::beimausbewegung(_guiereignisdaten *ep){
                                if(hauptfenster->testmodus)return;
                                _tg dx,dy;
                                _vektor3<_tg> v;
                                dx=altepos[0]-ep->maus.x;
                                dy=altepos[1]-ep->maus.y;
                                _win::_tastatur ta;
                                
                                switch(modus){
                                
                                case 0:
                                 if((ta.shift()==false)&&(links==true)&&(rechts==false)&&kamera->orthonormal()){
                                  _editionskopplung*e;
                                  pruefenkollisionkopplungen(_vektor2<_tg>(ep->maus.x,ep->maus.y),e);
                                  if(e){
                                   modus=1;
                                   editionskopplung=e;
                                   hauptfenster->zeichnen();
                                  };
                                 };
                                
                                
                                
                                
                                
                                
                                
                                
                                
                                
                                //hauptfenster->letzteanwahl=-10000;
                                //if(kamera->orthonormal()==false) hauptfenster->letzteanwahl=0;
                                if(ta.shift()){
                                 if((links==true)&&(rechts==false)){
                                  if(kamera->orthonormal()){
                                   dx*=0.002;
                                   dy*=0.002;
                                   v=kamera->ebene(0)*dx + kamera->ebene(1)*-dy;
                                   altepos.setzen(ep->maus.x,ep->maus.y);
                                   if(hauptfenster->rasterverwenden){
                                    bewegungsakku+=v;
                                    _tg rb=hauptfenster->snapping;
                                    int x,y,z;
                                    x=(int)(bewegungsakku[0]/rb);
                                    y=(int)(bewegungsakku[1]/rb);
                                    z=(int)(bewegungsakku[2]/rb);
                                    _vektor3<_tg> quant(_tg(x)*rb,_tg(y)*rb,_tg(z)*rb);
                                    bewegungsakku-=quant;
                                    v=quant;
                                   };
                                   //-------------------------------------------- LICHT VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahllicht){
                                    hauptfenster->anwahllicht->ort(hauptfenster->anwahllicht->ort()-v);
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- KNOTEN VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlknoten){
                                    hauptfenster->anwahlknoten->ort-=v;
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- Gravitation VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlgravitation){
                                    hauptfenster->anwahlgravitation->verschieben(-v);
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- feldelektrostatisch VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlfeldelektrostatisch){
                                    hauptfenster->anwahlfeldelektrostatisch->verschieben(-v);
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- feldmagnetostatisch VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlfeldmagnetostatisch){
                                    hauptfenster->anwahlfeldmagnetostatisch->verschieben(-v);
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- partikelquelle VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlpartikelquelle){
                                    hauptfenster->anwahlpartikelquelle->ort(hauptfenster->anwahlpartikelquelle->ort()-v);
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- KUGEL VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlkugel){
                                    hauptfenster->anwahlkugel->_kugel::ort(            hauptfenster->anwahlkugel->_kollidierbarkugel::ort()-v);
                                    hauptfenster->anwahlkugel->_kollidierbarkugel::ort(hauptfenster->anwahlkugel->_kollidierbarkugel::ort()-v);
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- VERTEX VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlvertexliste.erstes()){
                                    _listenknoten<_vertex>*lnvit;
                                    _liste<_netz> ln;
                                    iterierenliste(&hauptfenster->anwahlvertexliste,lnvit,
                                     lnvit->objekt()->ort(lnvit->objekt()->ort()-v);
                                     ln.einhaengenunredundant(lnvit->objekt()->netz());
                                    );
                                    _listenknoten<_netz>*nit;
                                    iterierenliste(&ln,nit,nit->objekt()->aktualisieren());
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- POLYGON VERSCHIEBEN -----------------------------------------
                                   if(hauptfenster->anwahlpolygonliste.erstes()){
                                    _vertex*vit;
                                    _listenknoten<_vertex>*lnvit;
                                    _listenknoten<_polygon>*lnpit;
                                    _liste<_netz> ln;
                                    _liste<_polygon>*lp=&hauptfenster->anwahlpolygonliste;
                                    iterierenliste(lp,lnpit,lnpit->objekt()->markierungvertex(1));
                                    iterierenliste(lp,lnpit,
                                     iterierenliste(lnpit->objekt(),lnvit,
                                      vit=lnvit->objekt();
                                      if(vit->markierung()==1){
                                       vit->markierung(0);
                                       vit->ort(vit->ort()-v);
                                      };
                                     );
                                     ln.einhaengenunredundant(lnpit->objekt()->netz());
                                    );
                                    _listenknoten<_netz>*nit;
                                    iterierenliste(&ln,nit,nit->objekt()->aktualisieren());
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- KANTE VERSCHIEBEN -----------------------------------------------
                                   if(hauptfenster->anwahlkanteliste.erstes()){
                                    _listenknoten<_verbindervertexpolygon>*lncit;
                                    _liste<_verbindervertexpolygon>*lc=&hauptfenster->anwahlkanteliste;
                                    _liste<_netz> ln;
                                    iterierenliste(lc,lncit,lncit->objekt()->vertex()->markierung(1);lncit->objekt()->naechstervertex()->markierung(1));                                    
                                    iterierenliste(lc,lncit,
                                     if(lncit->objekt()->vertex()->markierung()==1){
                                      lncit->objekt()->vertex()->markierung(0);
                                      lncit->objekt()->vertex()->ort(lncit->objekt()->vertex()->ort()-v);
                                      ln.einhaengenunredundant(lncit->objekt()->vertex()->netz());
                                     };
                                     if(lncit->objekt()->naechstervertex()->markierung()==1){
                                      lncit->objekt()->naechstervertex()->markierung(0);
                                      lncit->objekt()->naechstervertex()->ort(lncit->objekt()->naechstervertex()->ort()-v);
                                      ln.einhaengenunredundant(lncit->objekt()->naechstervertex()->netz());
                                     };
                                    );
                                    _listenknoten<_netz>*nit;
                                    iterierenliste(&ln,nit,nit->objekt()->aktualisieren());
                                    hauptfenster->zeichnen();
                                   };
                                   //-------------------------------------------- NETZ VERSCHIEBEN ------------------------------------------------
                                   if(hauptfenster->anwahlnetzliste.erstes()){
                                    _listenknoten<_netz>*nit;
                                    _polygon*p;
                                    _netz*n;
                                    _tg x0,x1,y0,y1,z0,z1;
                                    if(hauptfenster->anwahlnetzliste.anfang(nit))do{
                                     n=nit->objekt();
                                     n->verschiebenvertex(-v);
                                     if(n->anfang(p))do{
                                      p->_liste<_baumoctalwuerfel<_polygon,_tg> >::aushaengen();
                                      p->umgrenzungsquader(x0,x1,y0,y1,z0,z1);
                                      hauptfenster->corundwelt->_baumoctal<_polygon,_tg>::einhaengen(p,x0,x1,y0,y1,z0,z1);
                                     }while(n->naechstes(p));
                                     n->aktualisieren();
                                    }while(hauptfenster->anwahlnetzliste.naechstes(nit));
                                    hauptfenster->zeichnen();
                                   };
                                   
                                   
                                  };
                                 };
                                }else{
                                 //----------------------------------------- Kamera verschieben --------------------------------------------------
                                 if((modus==0)&&(links==true)&&(rechts==false)){
                                  if(kamera->orthonormal()){
                                   dx*=0.005;
                                   dy*=0.005;
                                   v=kamera->ebene(0)*dx + kamera->ebene(1)*-dy;
                                  }else{
                                  // dx*=0.01;
                                  // dy*=0.01;
                                   v=kamera->ebenenormalisiert(0)*dx*0.1 + kamera->ebenenormalisiert(1)*-dy*0.1;
                                  }
                                  kamera->bewegen(v);
                                  altepos.setzen(ep->maus.x,ep->maus.y);
                                  neuzeichnen();
                                   if(sichtkopplung0){
                                    sichtkopplung0->neuzeichnen();
                                    sichtkopplung1->neuzeichnen();
                                   };                                    
                                 };
                                 if((links==true)&&(rechts==true)){
                                  if(kamera->orthonormal()){
                                   if(dy!=0){
                                    dy*=0.005;
                                    if(dy>1) dy=1;
                                    if(dy<-1) dy=-1;
                                    dy+=1;
                                    kamera->groesse(kamera->groesse(1)*dy,kamera->groesse(1)*dy);
                                   };
                                   //dx*=0.01;
                                  // v=kamera->ebene(0)*dx;
                                  // kamera->bewegen(v);
                                   altepos.setzen(ep->maus.x,ep->maus.y);
                                   neuzeichnen();
                                   if(sichtkopplung0){
                                    sichtkopplung0->neuzeichnen();
                                    sichtkopplung1->neuzeichnen();
                                   };                                   
                                  }else{
                                   _vektor3<_tg> vn=kamera->vektor();
                                   vn.normalisieren();
                                   v=vn*-dy*0.1+kamera->ebenenormalisiert(0)*dx*0.1;
                                   kamera->bewegen(v);
                                   altepos.setzen(ep->maus.x,ep->maus.y);
                                   neuzeichnen();
                                  };
                                 };
                                 //--------------------------------------------- KAMERA ROTIEREN -------------------------------------------------------
                                 if((links==false)&&(rechts==true)){
                                  if(kamera->orthonormal()==false){
                                   _vektor3<_tg> o=*kamera;
                                   kamera->bewegen(hauptfenster->corundwelt->kb,_vektor2<_tg>(-dx*0.9,dy*0.9),1);
                                   kamera->setzen(o);
                                   altepos.setzen(ep->maus.x,ep->maus.y);
                                   neuzeichnen();

                                  };
                                 };
                                };
                                break;
                                
                                
                                
                                
                                
                                
                                case 1:
                                 if((links==true)&&(rechts==false)){
                                 dx*=0.002;
                                 dy*=0.002;
                                 v=kamera->ebene(0)*dx + kamera->ebene(1)*-dy;
                                 altepos.setzen(ep->maus.x,ep->maus.y);
                                 if(hauptfenster->rasterverwenden){
                                  bewegungsakku+=v;
                                  _tg rb=hauptfenster->snapping;
                                  int x,y,z;
                                  x=(int)(bewegungsakku[0]/rb);
                                  y=(int)(bewegungsakku[1]/rb);
                                  z=(int)(bewegungsakku[2]/rb);
                                  _vektor3<_tg> quant(_tg(x)*rb,_tg(y)*rb,_tg(z)*rb);
                                  bewegungsakku-=quant;
                                  v=quant;
                                 };
                                 editionskopplung->verschieben(-v);
                                 hauptfenster->zeichnen();
                                 }else{
                                  modus=0;
                                  editionskopplung=0;
                                 };
                                 break;
                                };                                
                                  
                                
                                
                                
                                
                                
};
bool _ansicht::innerhalbtiefe(_polygon*p,_tg c0,_tg c1){
								if((istxz==false)&&(istxy==false)&&(istyz==false)) return(true);
								_vektor3<_tg> m=p->mitte();
								_tg c;
								if(istxz) c=m.y(); else
								if(istxy) c=m.z(); else
								if(istyz) c=m.x();
								
								if((c>c0)&&(c<c1)) return(true); else return(false);
};
void _ansicht::sichttiefe(_tg&c0,_tg&c1){
								if((istxz==false)&&(istxy==false)&&(istyz==false)) return;
								_tg c00,c01,c10,c11,h0,h1;
								h0=sichtkopplung0->kamera->groesse(0);
								h1=sichtkopplung1->kamera->groesse(0);
								if(istxz){
								 c00=sichtkopplung0->kamera->y()-h0;
								 c01=sichtkopplung0->kamera->y()+h0;
								 c10=sichtkopplung1->kamera->y()-h1;
								 c11=sichtkopplung1->kamera->y()+h1;
								 c0=minimum<_tg>(c00,c01,c10,c11);
								 c1=maximum<_tg>(c00,c01,c10,c11);
								 return;
								};
								if(istxy){
								 c00=sichtkopplung0->kamera->z()-h0;
								 c01=sichtkopplung0->kamera->z()+h0;
								 c10=sichtkopplung1->kamera->z()-h1;
								 c11=sichtkopplung1->kamera->z()+h1;
								 c0=minimum<_tg>(c00,c01,c10,c11);
								 c1=maximum<_tg>(c00,c01,c10,c11);
								 return;
								};
								if(istyz){
								 c00=sichtkopplung0->kamera->x()-h0;
								 c01=sichtkopplung0->kamera->x()+h0;
								 c10=sichtkopplung1->kamera->x()-h1;
								 c11=sichtkopplung1->kamera->x()+h1;
								 c0=minimum<_tg>(c00,c01,c10,c11);
								 c1=maximum<_tg>(c00,c01,c10,c11);
								 return;
								};
};
void _ansicht::zeichnengrid(_tg teilung){
                                   _vektor4<_to> colteilung(0.2,0.2,0.2,1);
                                   _vektor4<_to> colteilungsub(0.1,0.1,0.1,1);
                                   _vektor4<_to> colteilungnull(0.6,0.6,0.6,0.7);
								   _vektor3<_tg> o0,o1;
								  
								   //-----------------------------------------------------------------------------------------------------
                                   grafik->transparenz(true);
                                   grafik->transparenzadditiv();
                                   grafik->beleuchtung(false);
                                   grafik->textur(false);
                                   grafik->tiefenbufferkondition(false);
                                   grafik->material(false);
                                   grafik->anzeigebufferschreiben(true);
								   
								   //-----------------------------------------------------------------------------------------------TOP XZ
								   if(istxz){
								    _tg kl=kamera->ebene(0).laenge();
								    _tg d=1;
								    _tg f=kl*2;
								    while((f/d)>teilung) d*=teilung;//höchstens 8 hauptteillinien
								    while((f/d)<1)       d/=teilung;//mindestens 1 hauptteillinie
								    _tg z0=kamera->z()-kl;
								    _tg z1=kamera->z()+kl;
								    _tg x0=kamera->x()-kl;
								    _tg x1=kamera->x()+kl;

									int isx=0;
								    _tg sx=0;
								    while(sx>x0) {sx-=d;isx++;};
								    while((sx+d)<x0) {sx+=d;isx--;};
								    
								    for(_tg p=sx;p<x1;p+=d){
								     _tg dd=d/teilung;
								     _tg pp=p+dd;
								     for(int tt=0;tt<int(teilung)-1;tt++){
								      o0.setzen(pp,0,z0);
								      o1.setzen(pp,0,z1);
								      grafik->zeichnen(o0,o1,colteilungsub);
								      pp+=dd;
								     };
								     o0.setzen(p,0,z0);
								     o1.setzen(p,0,z1);
								     if(isx==0) grafik->zeichnen(o0,o1,colteilungnull); else grafik->zeichnen(o0,o1,colteilung);
								     isx--;
								    };

									int isz=0;
								    _tg sz=0;
								    while(sz>z0) {sz-=d;isz++;};
								    while((sz+d)<z0) {sz+=d;isz--;};
								    
								    for(_tg p=sz;p<z1;p+=d){
								     _tg dd=d/teilung;
								     _tg pp=p+dd;
								     for(int tt=0;tt<int(teilung)-1;tt++){
								      o0.setzen(x0,0,pp);
								      o1.setzen(x1,0,pp);
								      grafik->zeichnen(o0,o1,colteilungsub);
								      pp+=dd;
								     };
								     o0.setzen(x0,0,p);
								     o1.setzen(x1,0,p);
								     if(isz==0) grafik->zeichnen(o0,o1,colteilungnull); else grafik->zeichnen(o0,o1,colteilung);
								     isz--;
								    };
                                   };
								   //-----------------------------------------------------------------------------------------------SIDE XY
								   if(istxy){
								    _tg kl=kamera->ebene(0).laenge();
								    _tg d=1;
								    _tg f=kl*2;
								    while((f/d)>teilung) d*=teilung;//höchstens 8 hauptteillinien
								    while((f/d)<1)       d/=teilung;//mindestens 1 hauptteillinie
								    _tg x0=kamera->x()-kl;
								    _tg x1=kamera->x()+kl;
								    _tg y0=kamera->y()-kl;
								    _tg y1=kamera->y()+kl;

									int isx=0;
								    _tg sx=0;
								    while(sx>x0) {sx-=d;isx++;};
								    while((sx+d)<x0) {sx+=d;isx--;};
								    
								    for(_tg p=sx;p<x1;p+=d){
								     _tg dd=d/teilung;
								     _tg pp=p+dd;
								     for(int tt=0;tt<int(teilung)-1;tt++){
								      o0.setzen(pp,y0,0);
								      o1.setzen(pp,y1,0);
								      grafik->zeichnen(o0,o1,colteilungsub);
								      pp+=dd;
								     };
								     o0.setzen(p,y0,0);
								     o1.setzen(p,y1,0);
								     if(isx==0) grafik->zeichnen(o0,o1,colteilungnull); else grafik->zeichnen(o0,o1,colteilung);
								     isx--;
								    };

									int isy=0;
								    _tg sy=0;
								    while(sy>y0) {sy-=d;isy++;};
								    while((sy+d)<y0) {sy+=d;isy--;};
								    
								    for(_tg p=sy;p<y1;p+=d){
								     _tg dd=d/teilung;
								     _tg pp=p+dd;
								     for(int tt=0;tt<int(teilung)-1;tt++){
								      o0.setzen(x0,pp,0);
								      o1.setzen(x1,pp,0);
								      grafik->zeichnen(o0,o1,colteilungsub);
								      pp+=dd;
								     };
								     o0.setzen(x0,p,0);
								     o1.setzen(x1,p,0);
								     if(isy==0) grafik->zeichnen(o0,o1,colteilungnull); else grafik->zeichnen(o0,o1,colteilung);
								     isy--;
								    };
								   
                                   };
								   //-----------------------------------------------------------------------------------------------SIDE YZ
								   if(istyz){
								    _tg kl=kamera->ebene(0).laenge();
								    _tg d=1;
								    _tg f=kl*2;
								    while((f/d)>teilung) d*=teilung;//höchstens 8 hauptteillinien
								    while((f/d)<1)       d/=teilung;//mindestens 1 hauptteillinie
								    _tg z0=kamera->z()-kl;
								    _tg z1=kamera->z()+kl;
								    _tg y0=kamera->y()-kl;
								    _tg y1=kamera->y()+kl;

									int isz=0;
								    _tg sz=0;
								    while(sz>z0) {sz-=d;isz++;};
								    while((sz+d)<z0) {sz+=d;isz--;};
								    
								    for(_tg p=sz;p<z1;p+=d){
								     _tg dd=d/teilung;
								     _tg pp=p+dd;
								     for(int tt=0;tt<int(teilung)-1;tt++){
								      o0.setzen(0,y0,pp);
								      o1.setzen(0,y1,pp);
								      grafik->zeichnen(o0,o1,colteilungsub);
								      pp+=dd;
								     };
								     o0.setzen(0,y0,p);
								     o1.setzen(0,y1,p);
								     if(isz==0) grafik->zeichnen(o0,o1,colteilungnull); else grafik->zeichnen(o0,o1,colteilung);
								     isz--;
								    };

									int isy=0;
								    _tg sy=0;
								    while(sy>y0) {sy-=d;isy++;};
								    while((sy+d)<y0) {sy+=d;isy--;};
								    
								    for(_tg p=sy;p<y1;p+=d){
								     _tg dd=d/teilung;
								     _tg pp=p+dd;
								     for(int tt=0;tt<int(teilung)-1;tt++){
								      o0.setzen(0,pp,z0);
								      o1.setzen(0,pp,z1);
								      grafik->zeichnen(o0,o1,colteilungsub);
								      pp+=dd;
								     };
								     o0.setzen(0,p,z0);
								     o1.setzen(0,p,z1);
								     if(isy==0) grafik->zeichnen(o0,o1,colteilungnull); else grafik->zeichnen(o0,o1,colteilung);
								     isy--;
								    };
                                   };
                                   
};
void _ansicht::zeichnen(_guiereignisdaten *){
                                grafik->aktivitaet(true);
                                if(hauptfenster->corundwelt){
                                
                                 if(grafik->szenebeginn()){
                                  grafik->validieren(); 
                                  _corundwelt*ow=hauptfenster->corundwelt;
                                  _welt*welt=ow->welt;
                                  grafik->anzeigebufferschreiben(true);
                                  grafik->anzeigebufferloeschfarbe(farbe[0],farbe[1],farbe[2],farbe[3]);//glClearColor(farbe[0],farbe[1],farbe[2],farbe[3]);
                                  grafik->allebufferloeschen();

                                  welt->transformierenglobal(grafik,kamera);
								
								  _tg c0=-1000000;//alle polygone sollen im bereich c0,c1 gezoichnet werden mit flaeche
								  _tg c1=+1000000;
								  sichttiefe(c0,c1);
                                  //----------------------------------------- raster zeichnen ---------------------------------------------                                 
                                  if(kamera->orthonormal()){
                                   if(hauptfenster->rasterzeichnen){
                                    zeichnengrid(hauptfenster->rasterbreite);
                                   };
                                  };
                                  //------------------------------------------------------- welt zeichnen -------------------------------------
                                  grafik->textur(true);//glEnable(GL_TEXTURE_2D);
                                  grafik->transparenz(true);//glEnable(GL_BLEND);
                                  grafik->tiefenbufferkondition(false);//glDisable(GL_DEPTH_TEST);
                                  grafik->transparenzmultiplikativ();//glBlendFunc(GL_ONE,GL_ONE);
                                  _netz*nit;
                                  int nid=0;
                                  _weltdebugpfeil*wp=new _weltdebugpfeil(welt,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0),0.1,0.05,_vektor4<_to>(1,0,0,1));
                                  _weltdebugkreuz*wc=new _weltdebugkreuz(welt,_vektor3<_tg>(0,0,0),0.3,_vektor4<_to>(1,0,0,1));
                                  _weltdebugkugel*ws=new _weltdebugkugel(welt,_vektor3<_tg>(0,0,0),0.1,_vektor4<_to>(1,0,0,1));
                                  _weltdebugtext* wt=new _weltdebugtext( welt,"ok",_vektor3<_tg>(0,0,0),_vektor3<_tg>(2,0,0),_vektor3<_tg>(0,0,0.5),_vektor4<_to>(1,0,0,1));
                                  _weltdebugtext* wt2=new _weltdebugtext( welt,"ok",_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,0.25),_vektor4<_to>(1,0,0,1));
                                  _weltdebugzylinder*wz=new _weltdebugzylinder(welt,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,1,0),0.1,_vektor4<_to>(1,0,0,1));
                                  _licht<_tg,_to>*lit;
                                  _corundknoten*knit;
                                  _gravitation<_tg>*git;
                                  _feldelektrostatisch<_tg>*efit;
                                  _feldmagnetostatisch<_tg>*bfit;
                                  _partikelquelle*pqit;
                                  _polygon*pit;
                                  _weltdebug*dit;
                                  _corundkugel*oit; 
                                  _listenknoten<_polygon>*lnpit;
                                  _listenknoten<_netz>*lnnit;
                                  _listenknoten<_vertex>*lnvit;
                                  _listenknoten<_verbindervertexpolygon>*lncit;
                                  _verbindervertexpolygon*cit;
                                  
                                  /*
                                  if(kamera->orthonormal()==false){
                                   //Zeitmessung
                                   _win::_zeit*zz=new _win::_zeit();
                                   int zzstart=zz->system();
                                    _verbindervertexpolygon*pvcp;
                                    _verbindervertexpolygon*vcp0;
                                    _verbindervertexpolygon*vcp1;
                                    _vertex*vit0;
                                    _vertex*vit1;
                                   for (int u0=0;u0<1000;u0++){
                                    if(welt->anfang(nit))do{
                                     if(nit->anfang(pit))do{
                                     // iterierendreieck(pit,,);
                                     }while(nit->naechstes(pit));
                                    }while(welt->naechstes(nit));
                                   };
                                  // _zeichenkette<_tt> wixzz=L"Zeitmessung dms="+;
                                   L->l("Fickzeit =",int(zz->system()-zzstart));
                                  // hauptfenster->statusbar->text(2,wixzz.daten());
                                   delete zz;
                                  };*/
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  
                                  if(welt->anfang(nit))do{
                                   bool zonennetz=nit->zonennetz();
                                   int markverb;
                                   if(nit->anfang(pit)) if(pit->anfang(lnvit)) markverb=static_cast<_verbindervertexpolygon*>(lnvit)->markierung();
                                   //nit->markierungverbinder(1);
                                   grafik->textur(false);
                                   
                                   if(nit->anfang(pit))do{
                                 
                                    bool td=pit->verwendentexturdynamisch();
                                    bool zk=pit->zeichnenkante();
                                    bool zn=pit->zeichnennormale();
                                    bool zz=pit->zweiseitig();
                                    bool zf=pit->zeichnenflaeche();
                                    pit->verwendentexturdynamisch(false);
                                    pit->zeichnennormale(true);
                                    pit->zeichnenkante(true);
                                    pit->bindenmaskierung(grafik);
                                    pit->bindenzweiseitigkeit(grafik);
                                    if(zonennetz==false){
                                     if((hauptfenster->anwahlpolygonliste.suchen(pit,lnpit)==false)&&(hauptfenster->anwahlnetzliste.suchen(nit,lnnit)==false)) {
                                      //pit->zeichnenflaeche(true);
                                      bool i=innerhalbtiefe(pit,c0,c1);
                                      if(i==false) {
                                       pit->zeichnenflaeche(false);
                                       pit->farbekante(_vektor4<_to>(0.0,0.1,0.9,0.2));
                                      }else{
                                       pit->farbekante(_vektor4<_to>(1,1,0,0.3));
                                      };                                     
                                      pit->zeichnen(grafik,_vektor4<_to>(1,1,1,0.5),markverb); 
                                     }else{
                                      //selektion
                                      pit->zweiseitig(true);
                                      pit->zeichnenflaeche(true);
                                      pit->bindenzweiseitigkeit(grafik);
                                      pit->farbekante(_vektor4<_to>(1,0,0,0.9));
                                      pit->zeichnen(grafik,_vektor4<_to>(1,1,1,1),markverb);
                                     };
                                    }else{
                                     pit->farbekante(_vektor4<_to>(1,0,0.8,1));
                                     pit->zeichnen(grafik,_vektor4<_to>(1,0.0,0.3,0.5),markverb);
                                    };
                                    pit->zeichnenflaeche(zf);
                                    pit->verwendentexturdynamisch(td);
                                    pit->zeichnennormale(zn);
                                    pit->zeichnenkante(zk);
                                    pit->zweiseitig(zz);
                                   }while(nit->naechstes(pit));
                                   if(nit->keinbsp()==false){
                                  //  wt->text(nid);
                                  //  wt->zeichnen(grafik);
                                    nid++;
                                   };
                                  }while(welt->naechstes(nit));
                                  iterierenliste(&hauptfenster->anwahlvertexliste,lnvit,
                                   wc->ort(lnvit->objekt()->ort());
                                   wc->zeichnen(grafik);
                                  );
                                  iterierenliste(&hauptfenster->anwahlkanteliste,lncit,
                                   wp->ort(lncit->objekt()->vertex()->ort(),lncit->objekt()->naechstervertex()->ort());
                                   wp->zeichnen(grafik);
                                  );
                                  //--------------------- bänder und federn zeichnen ---------------------------------
                                  _corundfeder*cfedit;
                                  _corundgummiband*cgubit;
                                  if(ow->anfang(cfedit))do{
                                   cfedit->zeichnen(grafik);
                                  }while(ow->naechstes(cfedit));
                                  if(ow->anfang(cgubit))do{
                                   cgubit->zeichnen(grafik);
                                  }while(ow->naechstes(cgubit));
                                  //--------------------- Lichter zeichnen ---------------------------------
                                  _weltdebugkugel*wk=new _weltdebugkugel(welt,_vektor3<_tg>(0,0,0),0.3,_vektor4<_to>(1,1,1,1));
                                  if(welt->anfang(lit))do{
                                   wk->ort(lit->ort());
                                   wk->farbe(_vektor4<_to>(lit->farbedynamisch()[0],lit->farbedynamisch()[1],lit->farbedynamisch()[2],1));
                                   wk->zeichnen(grafik);
                                   wt->farbe(_vektor4<_to>(0,1,0,1));
                                   wt->text("Licht");
                                   wt->ort(_vektor3<_tg>(-1,0,-1)+lit->ort());
                                   wt->zeichnen(grafik);
                                   if(hauptfenster->anwahllicht==lit){
                                    wk->farbe(_vektor4<_to>(1,0,0,1));
                                    wk->radius(0.4);
                                    wk->zeichnen(grafik);
                                    wk->radius(0.3);                                   
                                    wt->farbe(_vektor4<_to>(1,0,0,1));
                                    wt->ort(_vektor3<_tg>(-1,0.1,-1)+lit->ort());
                                    wt->zeichnen(grafik);
                                   };
                                  }while(welt->naechstes(lit));
                                  //--------------------- Knoten zeichnen ---------------------------------
                                  if(ow->anfang(knit))do{
                                   wk->ort(knit->ort);
                                   wk->farbe(_vektor4<_to>(1,1,1,1));
                                   wk->zeichnen(grafik);
                                   wt->farbe(_vektor4<_to>(0,1,0,1));
                                   _zeichenkette<char> h="Knoten";
                                   char buf[128];
                                   _itoa(knit->index,buf,10);
                                   h+=buf;
                                   wt->text(h);
                                   wt->ort(_vektor3<_tg>(-1,0,-1)+knit->ort);
                                   wt->zeichnen(grafik);
                                   if(hauptfenster->anwahlknoten==knit){
                                    wk->farbe(_vektor4<_to>(1,0,0,1));
                                    wk->radius(0.4);
                                    wk->zeichnen(grafik);
                                    wk->radius(0.3);                                   
                                    wt->farbe(_vektor4<_to>(1,0,0,1));
                                    wt->ort(_vektor3<_tg>(-1,0.1,-1)+knit->ort);
                                    wt->zeichnen(grafik);
                                   };
                                  }while(ow->naechstes(knit));
                                  //--------------------- Partikelquellen zeichnen -----------------------------------
                                  wk->radius(0.5);        
                                  if(welt->anfang(pqit))do{
                                   wk->ort(pqit->ort());
                                   wk->farbe(_vektor4<_to>(1,1,1,1));
                                   wk->zeichnen(grafik);
                                   wt2->farbe(_vektor4<_to>(0,1,0,1));
                                   wt2->text("Partikel");
                                   wt2->ort(_vektor3<_tg>(-0.5,0,-1)+pqit->ort());
                                   wt2->zeichnen(grafik);
                                   wt2->text("quelle");
                                   wt2->ort(_vektor3<_tg>(-0.5,0,-1.26)+pqit->ort());
                                   wt2->zeichnen(grafik);
                                   if(hauptfenster->anwahlpartikelquelle==pqit){
                                    wk->farbe(_vektor4<_to>(1,0,0,1));
                                    wk->radius(0.7);
                                    wk->zeichnen(grafik);
                                    wk->radius(0.5);                                   
                                    wp->farbe(_vektor4<_to>(1,0,0,1));
                                    wt2->farbe(_vektor4<_to>(1,0,0,1));
                                    wt2->text("Partikel");
                                    wt2->ort(_vektor3<_tg>(-0.5,0.1,-1)+pqit->ort());
                                    wt2->zeichnen(grafik);
                                    wt2->text("quelle");
                                    wt2->ort(_vektor3<_tg>(-0.5,0.1,-1.26)+pqit->ort());
                                    wt2->zeichnen(grafik);
                                   }else wp->farbe(_vektor4<_to>(0.1,0,0.8,1));
                                   wp->ort(0,pqit->ort());
                                   wp->ort(1,pqit->ort()+pqit->ortraum(0));
                                   wp->zeichnen(grafik);
                                   wp->ort(1,pqit->ort()+pqit->ortraum(1));
                                   wp->zeichnen(grafik);
                                   wp->ort(1,pqit->ort()+pqit->ortraum(2));
                                   wp->zeichnen(grafik);
                                   wp->ort(1,pqit->ort()-pqit->ortraum(0));
                                   wp->zeichnen(grafik);
                                   wp->ort(1,pqit->ort()-pqit->ortraum(1));
                                   wp->zeichnen(grafik);
                                   wp->ort(1,pqit->ort()-pqit->ortraum(2));
                                   wp->zeichnen(grafik); 
                                  }while(welt->naechstes(pqit));
                                  //--------------------- gravitationen zeichnen -----------------------------------
                                  if(welt->anfang(git))do{
                                   welt->zeichnenfeld(git,grafik,hauptfenster->anwahlgravitation==git,"Gravitation");
                                   if(hauptfenster->gfeldzeichnen)welt->zeichnenfeld(git,grafik,hauptfenster->gfeldanzahl);
                                  }while(welt->naechstes(git));
                                  //--------------------- feldelektrostatischen zeichnen -----------------------------------
                                  if(welt->anfang(efit))do{
                                   welt->zeichnenfeld(efit,grafik,hauptfenster->anwahlfeldelektrostatisch==efit,"E-Feld");
                                   if(hauptfenster->efeldzeichnen)welt->zeichnenfeld(efit,grafik,hauptfenster->efeldanzahl);
                                  }while(welt->naechstes(efit));
                                  //--------------------- feldmagnetostatischen zeichnen -----------------------------------
                                  if(welt->anfang(bfit))do{
                                   welt->zeichnenfeld(bfit,grafik,hauptfenster->anwahlfeldmagnetostatisch==bfit,"B-Feld");
                                   if(hauptfenster->bfeldzeichnen)welt->zeichnenfeld(bfit,grafik,hauptfenster->bfeldanzahl);
                                  }while(welt->naechstes(git));
                                  //-------------------- spinnen zeichnen -------------------------------------------
                                  _corundspinne*csit;
                                  if(ow->anfang(csit))do{
                                   csit->visualisieren();
                                  }while(ow->naechstes(csit));
                                  //-------------------- figuren zeichnen -------------------------------------------
                                  _corundfigur*cfit;
                                  if(ow->anfang(cfit))do{
                                   cfit->visualisieren();
                                  }while(ow->naechstes(cfit));
                                  //-------------------- kugeln zeichnen -------------------------------------------
                                  grafik->transparenz(false);//glDisable(GL_BLEND);
                                  grafik->tiefenbufferkondition(false);//glDisable(GL_DEPTH_TEST);
                                  grafik->maske(false);//glDisable(GL_ALPHA_TEST);
                                  grafik->ausschussflaeche(false);//glDisable(GL_CULL_FACE);
                                  wk->radius(0.5);
                                  if(ow->anfang(oit))do{
                                   _vektor3<_tg> port=oit->_kollidierbarkugel::ort();
			                       grafik->beleuchtung(false);//glDisable(GL_LIGHTING);
			                       grafik->textur(false);//glDisable(GL_TEXTURE_2D);
                                   grafik->kugel(port,oit->farbe,oit->_kollidierbarkugel::radius(),20,20);
                                   grafik->textur(true);//glEnable(GL_TEXTURE_2D);
			                       //glFrontFace(GL_CCW);
                                   wk->ort(oit->_kollidierbarkugel::ort());
                                   wk->farbe(_vektor4<_to>(oit->farbe[0],oit->farbe[1],oit->farbe[2],1));
                                   wk->zeichnen(grafik);
                                   if(oit->spieler==true) wt->text("Spieler"); else wt->text("Kugel");
                                   wt->farbe(_vektor4<_to>(0,1,0,1));
                                   wt->ort(_vektor3<_tg>(-1,0,-1)+oit->_kollidierbarkugel::ort());
                                   wt->zeichnen(grafik);
                                   if(hauptfenster->anwahlkugel==oit){
                                    wk->farbe(_vektor4<_to>(1,0,0,1));
                                    wk->radius(0.7);
                                    wk->zeichnen(grafik);
                                    wk->radius(0.5);                                   
                                    wt->farbe(_vektor4<_to>(1,0,0,1));
                                    wt->ort(_vektor3<_tg>(-1,0.1,-1)+oit->_kollidierbarkugel::ort());
                                    wt->zeichnen(grafik);
                                   };
                                  }while(ow->naechstes(oit));                                 
                                  grafik->ausschussflaeche(true);//glEnable(GL_CULL_FACE);
                                  //-------------------- kopplungen zeichnen -------------------------------------------
                                  _dynamischerdialog*ddit;
                                  _editionskopplung*ekit;
                                  if(hauptfenster->anfang(ddit))do{
                                   if(ddit->_listebasis<_editionskopplung>::anfang(ekit))do{
                                    ekit->zeichnen(grafik);
                                   }while(ddit->_listebasis<_editionskopplung>::naechstes(ekit));
                                  }while(hauptfenster->naechstes(ddit));
                                  //------------------------------------------------------------------------------------
                                  delete wk;
                                  delete wz;
                                  delete ws;
                                  delete wt;
                                  delete wt2;
                                  delete wp;
                                  delete wc;
                                  //-------------------- steine zeichnen -------------------------------------------
                                  _corundstein*osit;
                                  if(ow->anfang(osit))do{
                                   osit->zeichnen(grafik);
                                  }while(ow->naechstes(osit));
                                  //-------------------- böden zeichnen -------------------------------------------
                                  _corundboden*obit;
                                  if(ow->anfang(obit))do{
                                   obit->zeichnen(grafik);
                                  }while(ow->naechstes(obit));
                                  //------------------------- debug elemente zeichnen ------------------------------
                                  if(welt->anfang(dit))do{
                                   dit->zeichnen(grafik);
                                  }while(welt->naechstes(dit));
                                  //------------------------- baum zeichnen ------------------------------
                                  if(hauptfenster->baumzeichnen){
                                   ow->zeichnenbaum(grafik);
                                  };
                                  grafik->szeneende();
                                 };
                                 grafik->anzeigebufferumschalten();
                                }else{
                                 if(grafik->szenebeginn()){
                                  grafik->validieren(); 
                                  grafik->anzeigebufferloeschfarbe(farbe[0]*0.2,farbe[1]*0.2,farbe[2]*0.2,farbe[3]);//glClearColor(farbe[0],farbe[1],farbe[2],farbe[3]);
                                  grafik->anzeigebufferschreiben(true);//glColorMask(1,1,1,1);
                                  grafik->allebufferloeschen();
                                  grafik->szeneende();
                                 };
                                 grafik->anzeigebufferumschalten();
                                };
};
void _ansicht::zeichnensteinschablone(_netz*nit){
                                _polygon*pit;
                                //---------------
                                if(nit->anfang(pit))do{
                                 bool td=pit->verwendentexturdynamisch();
                                 bool zk=pit->zeichnenkante();
                                 bool zn=pit->zeichnennormale();
                                 pit->verwendentexturdynamisch(false);
                                 pit->zeichnennormale(true);
                                 pit->zeichnenkante(true);
                                 pit->bindenmaskierung(grafik);
                                 pit->bindenzweiseitigkeit(grafik);
                                 pit->farbekante(_vektor4<_to>(0,0,0.8,1));
                                 pit->zeichnen(grafik,_vektor4<_to>(0.0,0.0,0.3,1),0);
                                 pit->verwendentexturdynamisch(td);
                                 pit->zeichnennormale(zn);
                                 pit->zeichnenkante(zk);
                                }while(nit->naechstes(pit));
};

/*
GRAPHICS_API void screenToWorld(Float32 *destx, Float32 *desty, Int32 x, Int32 y, Int32 width, Int32 height, 
                                Float32 hfov, Float32 vfov, Float32 haspect, Float32 vaspect, Float32 znear) 
{ 
   Float32  halfwidth, halfheight; 
   Float64  left, right, top, bottom; 
   // ---------------------------------------------------------------- 
    
    
   calculate_projection(left, top, right, bottom, hfov, vfov, haspect, vaspect, znear); 
    
   halfwidth  = (width  - 1) * 0.5f; 
   halfheight = (height - 1) * 0.5f; 
    
   *destx = (x - halfwidth)  /  halfwidth  * Float32(right); 
   *desty = (y - halfheight) / -halfheight * Float32(top); 
}


 static void calculateProjection(Float64 &left, Float64 &top, Float64 &right, Float64 &bottom, 
                                Float32 hfov, Float32 vfov, Float32 haspect, Float32 vaspect, Float32 znear) 
{ 
   Float64  pi_over_360 = 1 / 360.0 * 3.1415926538; 
   // ----------------------------------------------------- 
    
    
   right  = znear * tan(hfov * pi_over_360) * haspect; 
   left   = -right; 
    
   top    = znear * tan(vfov * pi_over_360) * vaspect; 
   bottom = -top; 
}
*/


void _ansicht::pruefenkollisionkopplungen(const _vektor2<_tg>&m,_editionskopplung*&e){
                                e=0;
                                _corundwelt*ow=hauptfenster->corundwelt;
                                if(ow==0)return;
                                //int              viewport[4];
                                //double           umx, umy, umz;
                                //double           mvMatrix[16], projMatrix[16];

                                _vektoranalysis3<_tg> V3;
                                _vektor3<_tg> weltk;
                                _vektor3<_tg> geraetk;
                                grafik->aktivitaet(true);
                                
                                
                                //glGetIntegerv(GL_VIEWPORT, viewport); 
                                //glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix); 
                                //glGetDoublev(GL_PROJECTION_MATRIX, projMatrix); 
                                if(kamera->orthonormal()) {
                                 geraetk.setzen((double)m[0],(double)(m[1]),0.1);
                                 grafik->transformierenrueck(geraetk,weltk);
                                 //gluUnProject((double)m[0], (double)(viewport[3] - m[1]), 0.1, mvMatrix, projMatrix, viewport, &umx, &umy, &umz);  
                                 dir=kamera->vektor();
                                 dir.normalisieren();
                                 start=weltk;//.setzen(umx,umy,umz);
                                };
                                
                                
                                _editionskopplung*eit;
                                _vektor3<_tg> lot;
                                _tg minl=10e+12;
                                _tg aktl;
                                _dynamischerdialog*ddit;
                                if(hauptfenster->anfang(ddit))do{
                                 if(ddit->_listebasis<_editionskopplung>::anfang(eit))do{
                                  if(eit->aktiv()){
                                   lot=eit->abstand(start,dir);
                                   aktl=lot.laenge();
                                   if(aktl<=eit->editionsradius()){
                                    if(aktl<minl) {
                                     minl=aktl;
                                     e=eit;
                                     eit->farbe(_vektor4<_to>(0,1,0,1));
                                    };
                                   }else{
                                    eit->farbe(_vektor4<_to>(1,1,1,1));
                                   };
                                  };
                                 }while(ddit->_listebasis<_editionskopplung>::naechstes(eit));
                                }while(hauptfenster->naechstes(ddit));
                                
};
void _ansicht::loeschenanwahl(){
								if(hauptfenster->tastatur->control()==false){
                                 hauptfenster->loeschenanwahl();								
                                 hauptfenster->letzteanwahl=-10000;
                                 if(kamera->orthonormal()==false) hauptfenster->letzteanwahl=0;

                                }else{
                                 hauptfenster->letzteanwahl=-10000;
                                 if(kamera->orthonormal()==false) hauptfenster->letzteanwahl=0;
                                };
};

void _ansicht::pruefenkollision(const _vektor2<_tg>&m){
                                if(hauptfenster->corundwelt){
                                 _vektor2<_tg> d=m-alteschnittpos;
                                 if(d.laenge()>4){
                                  alteschnittpos=m;
                                  ls.loeschen();
                                  hauptfenster->letzteanwahl=-10000;
                                  if(kamera->orthonormal()==false) hauptfenster->letzteanwahl=0;
                                  _vektoranalysis3<_tg> V3;
                                  _corundwelt*ow=hauptfenster->corundwelt;
                                  _vektor3<_tg> geraetk;
                                  _vektor3<_tg> weltk;
                                  /*
                                  int              viewport[4];
                                  double           umx, umy, umz;
                                  double           mvMatrix[16], projMatrix[16];
                                  */
                                  grafik->aktivitaet(true);
                                  if(kamera->orthonormal()) {
                                   geraetk.setzen((double)m[0],(double)m[1],0.1);
                                   grafik->transformierenrueck(geraetk,weltk);
                                   start=weltk;
                                   dir=kamera->vektor();
                                   dir.normalisieren();
                                  }else{
                                   geraetk.setzen((double)m[0],(double)m[1],1);
                                   grafik->transformierenrueck(geraetk,weltk);
                                   dir.kopieren(weltk);
                                   dir.normalisieren(); 
                                   start=*kamera;
                                   /*
                                   _tg x,y,z;
                                   x=(_tg)umx;
                                   y=(_tg)umy;
                                   z=(_tg)umz;
                                   */
                                  
                                  };
                                  /*
                                  glGetIntegerv(GL_VIEWPORT, viewport); 
                                  glGetDoublev(GL_MODELVIEW_MATRIX, mvMatrix); 
                                  glGetDoublev(GL_PROJECTION_MATRIX, projMatrix); 
                                  if(kamera->orthonormal()) {
                                   gluUnProject((double)m[0], (double)(viewport[3] - m[1]), 0.1, mvMatrix, projMatrix, viewport, &umx, &umy, &umz);  
                                   dir=kamera->vektor();
                                   dir.normalisieren();
                                   start.setzen(umx,umy,umz);
                                  }else{
                                   gluUnProject((double)m[0], (double)(viewport[3] - m[1]), 1, mvMatrix, projMatrix, viewport, &umx, &umy, &umz);
                                   _tg x,y,z;
                                   x=(_tg)umx;
                                   y=(_tg)umy;
                                   z=(_tg)umz;
                                   dir.setzen(x,y,z);
                                   dir.normalisieren(); 
                                   start=*kamera;
                                  };*/
								  _tg c0=-1000000;//alle polygone sollen im bereich c0,c1 gezoichnet werden mit flaeche
								  _tg c1=+1000000;
                                  _welt*wit=hauptfenster->corundwelt->welt;
                                  _netz*nit;
                                  _polygon*pit;
                                  bool exist=false;
                                  _vektor3<_tg> h;
                                  _tg pa;
								  sichttiefe(c0,c1);                                 
                                  if(hauptfenster->tastatur->control()==false) hauptfenster->loeschenanwahl();
                                  //------------------------------- polygone kollidieren
                                  if(wit->anfang(nit))do{
                                   if(nit->anfang(pit))do{
                                    pit->berechnengroessterindex();
                                    pit->anwahl(0);
                                    pit->farbekante(_vektor4<_to>(0,1,0,0.5));
                                   }while(nit->naechstes(pit));
                                   if(nit->anfang(pit))do{
                                    _vertex*v0;
                                    _vertex*v1;
                                    _vertex*v2;
                                    _tg a,b,c;
                                    if(innerhalbtiefe(pit,c0,c1)) if(pit->schnittpunkt(start,dir*1000,nahenull,hauptfenster->letzteanwahl,+1000000,v0,v1,v2,a,b,c)){
                                   //  L->schreiben("POlygone kollidieren :");
                                   //  L->l("  start =",start);
                                   //  L->l("  dir =",dir*1000);
                                   //  L->l("  schnitt =",start+dir*1000*c);
                                   //  L->l("  c =",c);
                                   //  L->l("  la =",hauptfenster->letzteanwahl);
                                     exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->polygon==pit) exist=true;);if(exist==false) new _schnitt(&ls,pit,c);
                                    };
                                   }while(nit->naechstes(pit));
                                  }while(wit->naechstes(nit));
                                  //-------------------------------- lichter kollidieren 
                                  _licht<_tg,_to>*lit;
                                  if(wit->anfang(lit))do{
                                   V3.lotpunktgerade(lit->ort(),start,dir,h,pa);
                                   if(h.laenge()<0.5) {
                                    exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->licht==lit) exist=true;);if(exist==false) new _schnitt(&ls,lit,pa);
                                   };
                                  }while(wit->naechstes(lit));
                                  //-------------------------------- knoten kollidieren 
                                  _corundknoten*knit;
                                  if(ow->anfang(knit))do{
                                   V3.lotpunktgerade(knit->ort,start,dir,h,pa);
                                   if(h.laenge()<0.5) {
                                    exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->knoten==knit) exist=true;);if(exist==false) new _schnitt(&ls,knit,pa);
                                   };
                                  }while(ow->naechstes(knit));
                                  //-------------------------------- gravitationen kollidieren 
                                  _gravitation<_tg>*git;
                                  if(wit->anfang(git))do{
                                   V3.lotpunktgerade(git->_feld<_tg>::ort(),start,dir,h,pa);
                                   if(h.laenge()<0.4) {
                                    exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->gravitation==git) exist=true;);if(exist==false) new _schnitt(&ls,git,pa);
                                   };
                                  }while(wit->naechstes(git));
                                  //-------------------------------- feldelektrostatischen kollidieren 
                                  _feldelektrostatisch<_tg>*efit;
                                  if(wit->anfang(efit))do{
                                   V3.lotpunktgerade(efit->_feld<_tg>::ort(),start,dir,h,pa);
                                   if(h.laenge()<0.4) {
                                    exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->feldelektrostatisch==efit) exist=true;);if(exist==false) new _schnitt(&ls,efit,pa);
                                   };
                                  }while(wit->naechstes(efit)); 
                                  //-------------------------------- feldmagnetostatischen kollidieren 
                                  _feldmagnetostatisch<_tg>*bfit;
                                  if(wit->anfang(bfit))do{
                                   V3.lotpunktgerade(bfit->_feld<_tg>::ort(),start,dir,h,pa);
                                   if(h.laenge()<0.4) {
                                    exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->feldmagnetostatisch==bfit) exist=true;);if(exist==false) new _schnitt(&ls,bfit,pa);
                                   };
                                  }while(wit->naechstes(bfit));
                                  //-------------------------------- partikelquelleen kollidieren 
                                  _partikelquelle*pqit;
                                  if(wit->anfang(pqit))do{
                                   V3.lotpunktgerade(pqit->ort(),start,dir,h,pa);
                                   if(h.laenge()<0.5) {
                                    exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->partikelquelle==pqit) exist=true;);if(exist==false) new _schnitt(&ls,pqit,pa);
                                   };
                                  }while(wit->naechstes(pqit));
                                  //-------------------------------- kugeln kollidieren 
                                  _corundkugel*oit;
                                  if(hauptfenster->corundwelt->anfang(oit))do{
                                   V3.lotpunktgerade(oit->_kollidierbarkugel::ort(),start,dir,h,pa);
                                   if(h.laenge()<0.6) {
                                    exist=false;iterierenliste(&ls,lnsit,if(lnsit->objekt()->kugel==oit) exist=true;);if(exist==false) new _schnitt(&ls,oit,pa);
                                   };
                                  }while(hauptfenster->corundwelt->naechstes(oit));
                                  //------------------------------------------------------------------------------------------------------------------------------------------------------
                                  //------------------------------------------------------------------------------------------------------------------------------------------------------
                                  //-------------------------------- licht anwahl setzen 
                                  if(ls.anfang(lnsit)){
                                   if(lnsit->objekt()->licht){
                                    hauptfenster->anwahllicht=lnsit->objekt()->licht;
                                    hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                   };
                                  //}else loeschenanwahl();
                                  //-------------------------------- knoten anwahl setzen 
                                  //if(ls.anfang(lnsit)){
                                   if(lnsit->objekt()->knoten){
                                    hauptfenster->anwahlknoten=lnsit->objekt()->knoten;
                                    hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                   };
                                  //}else loeschenanwahl();
                                  //-------------------------------- gravitation anwahl setzen 
                                  //if(ls.anfang(lnsit)){
                                   if(lnsit->objekt()->gravitation){
                                    hauptfenster->anwahlgravitation=lnsit->objekt()->gravitation;
                                    hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                   };
                                  //}else loeschenanwahl();
                                  //-------------------------------- feldelektrostatisch anwahl setzen
                                  //if(ls.anfang(lnsit)){
                                   if(lnsit->objekt()->feldelektrostatisch){
                                    hauptfenster->anwahlfeldelektrostatisch=lnsit->objekt()->feldelektrostatisch;
                                    hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                   };
                                  //}else loeschenanwahl();
                                  //-------------------------------- feldmagnetostatisch anwahl setzen
                                  //if(ls.anfang(lnsit)){
                                   if(lnsit->objekt()->feldmagnetostatisch){
                                    hauptfenster->anwahlfeldmagnetostatisch=lnsit->objekt()->feldmagnetostatisch;
                                    hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                   };
                                  //}else loeschenanwahl();
                                  //-------------------------------- partikelquelle anwahl setzen 
                                  //if(ls.anfang(lnsit)){
                                   if(lnsit->objekt()->partikelquelle){
                                    hauptfenster->anwahlpartikelquelle=lnsit->objekt()->partikelquelle;
                                    hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                   };
                                  //}else loeschenanwahl();
                                  //-------------------------------- kugel anwahl setzen 
                                  //if(ls.anfang(lnsit)){
                                   if(lnsit->objekt()->kugel){
                                    hauptfenster->anwahlkugel=lnsit->objekt()->kugel;
                                    hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                   };
                                  //}else loeschenanwahl();
                                  //-------------------------------- polygonkompoentenanweahl prüfen 
                                  //ls.anfang(lnsit);
                                  //if(lnsit){
                                   pit=lnsit->objekt()->polygon;
                                   // L->l("  schnitttt = ",start+dir*1000*lnsit->kriterium());
                                   // L->l("  lsanzahl = ",(int)ls.anzahl());
                                   if(pit){
                                    anwaehlen(pit,start+dir*1000*lnsit->kriterium()); 
                                   };
                                  }else loeschenanwahl();
                                  //-------------------------------------------------------------------------------------------------------------------------------
                                  hauptfenster->zeichnen();
                                 }else{
                                  //alte schnittliste benutzten 
                                  //weiteriterieren
                                  if(hauptfenster->tastatur->control()==false) hauptfenster->loeschenanwahl();
                                  if(lnsit) {
                                   lnsit=lnsit->naechstes();
                                   _schnitt*sc=lnsit->objekt();
                                   _hauptfenster*hf=hauptfenster;
                                   if(sc->polygon) anwaehlen(sc->polygon,start+dir*1000*lnsit->kriterium());
                                   if(sc->licht) hf->anwahllicht=sc->licht;
                                   if(sc->knoten) hf->anwahlknoten=sc->knoten;
                                   if(sc->partikelquelle) hf->anwahlpartikelquelle=sc->partikelquelle;
                                   if(sc->gravitation) hf->anwahlgravitation=sc->gravitation;
                                   if(sc->feldelektrostatisch) hf->anwahlfeldelektrostatisch=sc->feldelektrostatisch;
                                   if(sc->feldmagnetostatisch) hf->anwahlfeldmagnetostatisch=sc->feldmagnetostatisch;
                                   if(sc->kugel) hf->anwahlkugel=sc->kugel;                                    
                                   hf->zeichnen();
                                   
                                  };
                                 };
								};
};





void _ansicht::anwaehlen(_polygon*pit,_vektor3<_tg> schnitt){
                                _vektoranalysis3<_tg> V3;
                                //-------------------------------- vertex anwahl setzen ------------------------------------
                                if(hauptfenster->toolbar->vertexanwahl->gesetzt()){
                                 _vektor3<_tg> h;
                                 _tg dna=1e+10;
                                 _vertex*vit;
                                 _vertex*vna;
                                 _listenknoten<_vertex>*lnvit;
                                 //vit=pit->vertex();
                                 //if(vit)do{
                                 if(pit->anfang(lnvit)) vna=lnvit->objekt();
                                 iterierenliste(pit,lnvit,
                                  vit=lnvit->objekt();
                                  h=schnitt-vit->ort();
                                  if(dna>h.laenge()){
                                   vna=vit;
                                   dna=h.laenge();
                                  };
                                 // vit=vit->naechstes(pit);
                                 //}while(vit!=pit->vertex());
                                 );
                                 //hauptfenster->anwahlvertex=vna;
                                 if(hauptfenster->tastatur->control()){//addieren
                                  _listenknoten<_vertex>*lv;
                                  if(hauptfenster->anwahlvertexliste.suchen(vna,lv)){
                                   delete lv;
                                  }else{
                                   hauptfenster->anwahlvertexliste.einhaengen(vna);
                                  };
                                 }else{
                                  hauptfenster->anwahlvertexliste.aushaengen();
                                  hauptfenster->anwahlvertexliste.einhaengen(vna);
                                 };
                                };
                                //-------------------------------- kanten anwahl setzen ------------------------------------
                                if(hauptfenster->toolbar->kantenanwahl->gesetzt()){
                                 _vektor3<_tg> h;
                                 //_vektor3<_tg> schnitt=start+dir*lnsit->kriterium();
                                 _tg dna=1e+10;
                                 _vertex*vit;
                                 _verbindervertexpolygon*vna;
                                 _vertex*vin;
                                 _listenknoten<_vertex>*lnvit;
                                 _verbindervertexpolygon*cit;
                                 //new _weltdebugkreuz(hauptfenster->corundwelt->welt,schnitt,0.3,_vektor4<_to>(0,1,0,1));
                                 //vit=pit->vertex();
                                 //if(vit)do{
                                 // cit=vit->connector(pit);
                                 // vin=cit->naechstervertex();
                                 iterierenliste(pit,lnvit,
                                  vit=lnvit->objekt();
                                  vin=lnvit->naechstes()->objekt();
                                  cit=static_cast<_verbindervertexpolygon*>(lnvit);
                                  V3.lotpunktgerade(schnitt,vit->ort(),vin->ort()-vit->ort(),h);
                                  if(dna>h.laenge()){
                                   vna=cit;
                                   dna=h.laenge();
                                  };
                                 // vit=vit->naechstes(pit);
                                 //}while(vit!=pit->vertex());
                                 );
                                 //hauptfenster->anwahlkante[0]=vna;
                                 //hauptfenster->anwahlkante[1]=vna->naechstes(pit);
                                 if(hauptfenster->tastatur->control()){//addieren
                                  _listenknoten<_verbindervertexpolygon>*lc;
                                  if(hauptfenster->anwahlkanteliste.suchen(vna,lc)){
                                   delete lc;
                                  }else{
                                   hauptfenster->anwahlkanteliste.einhaengen(vna);
                                  };
                                 }else{
                                  hauptfenster->anwahlkanteliste.aushaengen();
                                  hauptfenster->anwahlkanteliste.einhaengen(vna);
                                 };
                                };
                                //-------------------------------- polygon anwahl setzen ------------------------------------
                                if(hauptfenster->toolbar->polygonanwahl->gesetzt()){
                                 //pit->farbekante(_vektor4<_to>(1,0,0,0.5));
                                 //hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull*10;
                                 char la[1024];
                                 _gcvt(hauptfenster->letzteanwahl,20,la);
                                 hauptfenster->statusbar->text(2,ANSIToUnicode(la));
                                 //hauptfenster->anwahlpolygon=pit;
                                 if(hauptfenster->tastatur->control()){//addieren
                                  _listenknoten<_polygon>*lp;
                                  if(hauptfenster->anwahlpolygonliste.suchen(pit,lp)){
                                   delete lp;
                                  }else{
                                   hauptfenster->anwahlpolygonliste.einhaengen(pit);
                                  };
                                 }else{
                                  hauptfenster->anwahlpolygonliste.aushaengen();
                                  hauptfenster->anwahlpolygonliste.einhaengen(pit);
                                 };
                                };
                                //-------------------------------- netz anwahl setzen ------------------------------------
                                if(hauptfenster->toolbar->netzanwahl->gesetzt()){
                                 _netz*nit=pit->netz();
                                 //if(netz->anfang(pit))do{
                                 // pit->anwahl(1);
                                 // pit->farbekante(_vektor4<_to>(1,0,0,0.5));
                                 // hauptfenster->letzteanwahl=lnsit->kriterium()+nahenull;
                                 //}while(netz->naechstes(pit));
                                 //hauptfenster->anwahlnetz=netz;
                                 if(hauptfenster->tastatur->control()){//addieren
                                  _listenknoten<_netz>*ln;
                                  if(hauptfenster->anwahlnetzliste.suchen(nit,ln)){
                                   delete ln;
                                  }else{
                                   hauptfenster->anwahlnetzliste.einhaengen(nit);
                                  };
                                 }else{
                                  hauptfenster->anwahlnetzliste.aushaengen();
                                  hauptfenster->anwahlnetzliste.einhaengen(nit);
                                 };
                                 
                                };
};

void _ansicht::beibearbeitenlicht(_guiereignisdaten*){
                                if(hauptfenster->anwahllicht){
                                 hauptfenster->dyndialog->neusetzen(L"Angewähltes Licht bearbeiten");
                                 hauptfenster->anwahllicht->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beikopierenlicht(_guiereignisdaten*){
                                if(hauptfenster->anwahllicht){
                                 _licht<_tg,_to>*nl;
                                 hauptfenster->anwahllicht->kopieren(nl);
                                 hauptfenster->anwahllicht=nl;
                                 hauptfenster->zeichnen();
                                };
};
void _ansicht::beiloeschenlicht(_guiereignisdaten*){
                                if(hauptfenster->anwahllicht){
                                 delete hauptfenster->anwahllicht;
                                 loeschenschnittliste();
                                 hauptfenster->loeschenanwahl();
                                 hauptfenster->zeichnen();
                                };
};
void _ansicht::beibearbeitenknoten(_guiereignisdaten*){
                                if(hauptfenster->anwahlknoten){
                                 hauptfenster->dyndialog->neusetzen(L"Angewählten Knoten bearbeiten");
                                 hauptfenster->anwahlknoten->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beiloeschenknoten(_guiereignisdaten*){
                                if(hauptfenster->anwahlknoten){
                                 delete hauptfenster->anwahlknoten;
                                 loeschenschnittliste();
                                 hauptfenster->loeschenanwahl();
                                 hauptfenster->zeichnen();
                                };
};

void _ansicht::beibearbeitengravitation(_guiereignisdaten*){
                                if(hauptfenster->anwahlgravitation){
                                 hauptfenster->dyndialog->neusetzen(L"Angewählte Gravitation bearbeiten");
                                 hauptfenster->anwahlgravitation->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beiloeschengravitation(_guiereignisdaten*){
                                if(hauptfenster->anwahlgravitation){
                                 delete hauptfenster->anwahlgravitation;
                                 loeschenschnittliste();
                                 hauptfenster->loeschenanwahl();
                                 hauptfenster->zeichnen();
                                };
};



void _ansicht::beibearbeitenfeldelektrostatisch(_guiereignisdaten*){
                                if(hauptfenster->anwahlfeldelektrostatisch){
                                 hauptfenster->dyndialog->neusetzen(L"Angewählte elektrostatisches Feld bearbeiten");
                                 hauptfenster->anwahlfeldelektrostatisch->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beiloeschenfeldelektrostatisch(_guiereignisdaten*){
                                if(hauptfenster->anwahlfeldelektrostatisch){
                                 delete hauptfenster->anwahlfeldelektrostatisch;
                                 loeschenschnittliste();
                                 hauptfenster->loeschenanwahl();
                                 hauptfenster->zeichnen();
                                };
};

void _ansicht::beibearbeitenfeldmagnetostatisch(_guiereignisdaten*){
                                if(hauptfenster->anwahlfeldmagnetostatisch){
                                 hauptfenster->dyndialog->neusetzen(L"Angewählte magnetostatisches Feld bearbeiten");
                                 hauptfenster->anwahlfeldmagnetostatisch->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beiloeschenfeldmagnetostatisch(_guiereignisdaten*){
                                if(hauptfenster->anwahlfeldmagnetostatisch){
                                 delete hauptfenster->anwahlfeldmagnetostatisch;
                                 loeschenschnittliste();
                                 hauptfenster->loeschenanwahl();
                                 hauptfenster->zeichnen();
                                };
};

void _ansicht::beibearbeitenpartikelquelle(_guiereignisdaten*){
                                if(hauptfenster->anwahlpartikelquelle){
                                 hauptfenster->dyndialog->neusetzen(L"Angewählte Partikelquelle bearbeiten");
                                 hauptfenster->anwahlpartikelquelle->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beikopierenpartikelquelle(_guiereignisdaten*){
                                if(hauptfenster->anwahlpartikelquelle){
                                 _partikelquellesprite*ps=new _partikelquellesprite(hauptfenster->corundwelt->welt,hauptfenster->corundwelt->welt,hauptfenster->corundwelt->welt,hauptfenster->corundwelt->pzeit,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0),10,hauptfenster->corundwelt->textur[0]);
                                 _partikelquellesprite*pa=dynamic_cast<_partikelquellesprite*>(hauptfenster->anwahlpartikelquelle);
                                 if(pa){
                                  ps->kopieren(pa);
                                  ps->ort(ps->ort()+_vektor3<_tg>(1,0,0));
                                 };
                                 hauptfenster->zeichnen();
                                };
};
void _ansicht::beiloeschenpartikelquelle(_guiereignisdaten*){
                                if(hauptfenster->anwahlpartikelquelle){
                                 if(hauptfenster->corundwelt->istinternepartikelquelle(hauptfenster->anwahlpartikelquelle)){
                                  hauptfenster->information("Hinweis","Interne Partikelquellen der Welt dürfen nicht gelöscht werden.");
                                 }else{
                                  delete hauptfenster->anwahlpartikelquelle;
                                  loeschenschnittliste();
                                  hauptfenster->loeschenanwahl();
                                  hauptfenster->zeichnen();
                                 };
                                };
};
void _ansicht::beibearbeitenkugel(_guiereignisdaten*){
                                if(hauptfenster->anwahlkugel){
                                 hauptfenster->dyndialog->neusetzen(L"Angewählte Kugel bearbeiten");
                                 hauptfenster->anwahlkugel->hauptfenster=hauptfenster;
                                 hauptfenster->anwahlkugel->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beiloeschenkugel(_guiereignisdaten*){
                                if(hauptfenster->anwahlkugel){
                                 delete hauptfenster->anwahlkugel;
                                 ls.loeschen();
                                 hauptfenster->loeschenanwahl();
                                 hauptfenster->zeichnen();
                                };
};
void _ansicht::beibearbeitenpolygon(_guiereignisdaten*){
                                if(hauptfenster->anwahlpolygonliste.erstes()){
                                 hauptfenster->dyndialog->neusetzen(L"Angewähltes Polygon bearbeiten");
                                 hauptfenster->anwahlpolygonliste.erstes()->objekt()->einhaengendialog(hauptfenster->dyndialog);
                                 _listenknoten<_polygon>*pit;
                                 iterierenliste(&hauptfenster->anwahlpolygonliste,pit,hauptfenster->dyndialog->addiereneditierbar(pit->objekt()));
                                 hauptfenster->dyndialog->zeigen();
                                };
};
void _ansicht::beibearbeitenpolygontexturgeometrie(_guiereignisdaten*){
                                if(hauptfenster->anwahlpolygonliste.erstes()){
                                 hauptfenster->dtexturgeometrie->zeigen();
                                };
};
void _ansicht::beiloeschenpolygon(_guiereignisdaten*){
                                if(hauptfenster->anwahlpolygonliste.erstes()){
                                 _liste<_netz> ln;
                                 _listenknoten<_netz>*lnnit;
                                 _listenknoten<_polygon>*lnpit;
                                 iterierenliste((&hauptfenster->anwahlpolygonliste),lnpit,if(lnpit->objekt()->netz()) ln.einhaengenunredundant(lnpit->objekt()->netz()));
                                 iterierenliste((&hauptfenster->anwahlpolygonliste),lnpit,
                                  delete lnpit->objekt();
                                  lnpit->objekt(0);
                                 );
                                 hauptfenster->anwahlpolygonliste.aushaengen();
                                 iterierenliste((&ln),lnnit,
                                  _netz*n=lnnit->objekt();
                                  if(n->_listebasis<_polygon>::anzahl()==0) {
                                   delete n;
                                   lnnit->objekt(0);
                                  };
                                 );
                                 ln.aushaengen();
                                 //delete hauptfenster->anwahlpolygon;
                                 loeschenschnittliste();
                                 //if(nloesch) delete n;
                                 hauptfenster->loeschenanwahl();
                                 hauptfenster->zeichnen();
                                };
};
void _ansicht::beibearbeitennetz(_guiereignisdaten*){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 _netz*n=hauptfenster->anwahlnetzliste.erstes()->objekt();
                                 _corundstein*os=dynamic_cast<_corundstein*>(n);
                                 if(os)os->hauptfenster=hauptfenster;
                                 _corundobjekt*oo=dynamic_cast<_corundobjekt*>(n);
                                 if(oo)oo->hauptfenster=hauptfenster;
                                 _corundboden*ob=dynamic_cast<_corundboden*>(n);
                                 if(ob)ob->hauptfenster=hauptfenster;
                                 hauptfenster->dyndialog->neusetzen(L"Angewähltes Netz bearbeiten");
                                 n->einhaengendialog(hauptfenster->dyndialog);
                                 
                                 _listenknoten<_netz>*nit;
                                 iterierenliste(&hauptfenster->anwahlnetzliste,nit,hauptfenster->dyndialog->addiereneditierbar(nit->objekt()));
                                 
                                 hauptfenster->dyndialog->zeigen();
                                };
};

void _ansicht::holennetze(_netz*&n,_liste<_netz>*lop){
                                _liste<_netz>*l=&hauptfenster->anwahlnetzliste;
                                _listenknoten<_netz>*lnnit;
                                _netz*nit;
                                if(l->anzahl()==1){//mit dem rest der welt schneiden
                                 n=l->erstes()->objekt();
                                 iterierenliste(hauptfenster->corundwelt->welt,nit,if(nit!=n) lop->einhaengenunredundant(nit));
                                }else if(l->anzahl()>1){//mehrere netze sind angewählt, das erste mit dem rest der liste schneiden
                                 n=l->erstes()->objekt();
                                 iterierenliste(l,lnnit,if(lnnit->objekt()!=n) lop->einhaengenunredundant(lnnit->objekt()));
                                };
};

void _ansicht::beiintersektionnetz(_guiereignisdaten*){
                                _modifikationnetzintersektion I;
                                _liste<_netz> lop;
                                _listenknoten<_netz>*lnnit;
                                _netz*n;
                                _netz*nit;
                                holennetze(n,&lop);
                                iterierenliste(&lop,lnnit,
                                 nit=lnnit->objekt();
                                 if(nit->diskret()){
                                  if(nit->subtraktiv()==false){
                                   if(I.hatintersektion(n,nit)) I.bearbeiten(n,nit,0);
                                  }else{
                                   if(I.hatintersektion(n,nit)) I.bearbeiten(n,nit,1);
                                  };
                                 };
                                );                                
                                hauptfenster->zeichnen();
};
void _ansicht::beideintersektionnetz(_guiereignisdaten*){
                                _modifikationnetzintersektion I;
                                _liste<_netz> lop;
                                _listenknoten<_netz>*lnnit;
                                _netz*n;
                                _netz*nit;
                                holennetze(n,&lop);
                                iterierenliste(&lop,lnnit,
                                 nit=lnnit->objekt();
                                 if(nit->diskret()){
                                  if(nit->subtraktiv()==false){
                                   if(I.hatintersektion(n,nit)) I.bearbeiten(n,nit,1);
                                  }else{
                                   //if(I.hatintersektion(hauptfenster->anwahlnetz,nit)) I.bearbeiten(hauptfenster->anwahlnetz,nit,1);
                                  };
                                 };
                                );                                
                                hauptfenster->zeichnen();
};
void _ansicht::beivereinigungnetz(_guiereignisdaten*){
                                _modifikationnetzintersektion I;
                                _liste<_netz> lop;
                                _listenknoten<_netz>*lnnit;
                                _netz*n;
                                _netz*nit;
                                holennetze(n,&lop);
                                iterierenliste(&lop,lnnit,
                                 nit=lnnit->objekt();
                                 if(nit->diskret()){
                                  //if(nit->subtraktiv()==false){
                                  I.vereinigenohneschnitt(false);
                                  I.bearbeiten(n,nit,2);
                                  //}else{
                                  //I.bearbeiten(hauptfenster->anwahlnetz,nit,1);
                                  //};
                                 };
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beivereinigungnetzohneschnitt(_guiereignisdaten*){
                                _modifikationnetzintersektion I;
                                _liste<_netz> lop;
                                _listenknoten<_netz>*lnnit;
                                _netz*n;
                                _netz*nit;
                                holennetze(n,&lop);
                                iterierenliste(&lop,lnnit,
                                 nit=lnnit->objekt();
                                 n->vereinigen(nit);
                                 //if(nit->diskret()){
                                 // I.vereinigenohneschnitt(true);
                                 // I.bearbeiten(n,nit,2);
                                 //};
                                );
                                hauptfenster->loeschenanwahl();
                                hauptfenster->zeichnen();
};
void _ansicht::beivereinigungnetzwelt(_guiereignisdaten*){
                                _modifikationnetzintersektion I;
                                _liste<_netz> lop;
                                _listenknoten<_netz>*lnnit;
                                _netz*n;
                                _netz*nit;
                                holennetze(n,&lop);
                                iterierenliste(&lop,lnnit,
                                 nit=lnnit->objekt();
                                 if(nit->diskret()){
                                  if(nit->subtraktiv()==false){
                                   I.bearbeiten(n,nit,2);
                                  }else{
                                   //I.bearbeiten(hauptfenster->anwahlnetz,nit,1);
                                  };
                                 };
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beiteilungnetz(_guiereignisdaten*){
                                _modifikationnetzintersektion I;
                                _liste<_netz> lop;
                                _listenknoten<_netz>*lnnit;
                                _netz*n;
                                _netz*nit;
                                holennetze(n,&lop);
                                iterierenliste(&lop,lnnit,
                                 nit=lnnit->objekt();
                                 if(nit->diskret()){
                                  if(nit->subtraktiv()==false){
                                   I.bearbeiten(n,nit,3);
                                  }else{
                                   //I.bearbeiten(hauptfenster->anwahlnetz,nit,1);
                                  };
                                 };
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beinetztexturneuskalieren(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                _polygon*p;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,iterierenliste(nit->objekt(),p,
                                 p->neusetzentexturkoordinatenskaliert(0);
                                 p->aktualisieren();
                                ));
                                hauptfenster->zeichnen();                                  
};
void _ansicht::beinetzkomplanarenichtzeichnen(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 hauptfenster->netzkomplanarenichtzeichnen(nit->objekt());
                                );
};
void _ansicht::beinetzkomplanarenichtkollidieren(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 hauptfenster->netzkomplanarenichtkollidieren(nit->objekt());
                                );
};
void _ansicht::beinetzkomplanarekeinschattenwurflightmap(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 hauptfenster->netzkomplanarekeinschattenwurflightmap(nit->objekt());
                                );
};
void _ansicht::beifraktal(_guiereignisdaten*){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 hauptfenster->dfraktal->zeigen();
                                 hauptfenster->zeichnen();
                                };
};
void _ansicht::beibiegen(_guiereignisdaten*){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 hauptfenster->dbiegen->zeigen();
                                 hauptfenster->zeichnen();
                                }else hauptfenster->information("Hinweis","Sie müssen erst ein Netz anwählen, das verbogen werden kann.");;
};
void _ansicht::beirotieren(_guiereignisdaten*){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 hauptfenster->drotieren->zeigen();
                                 hauptfenster->zeichnen();
                                }else hauptfenster->information("Hinweis","Sie müssen erst ein Netz anwählen, das verbogen werden kann.");;
};
void _ansicht::beiverdrehen(_guiereignisdaten*){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 hauptfenster->dverdrehen->zeigen();
                                 hauptfenster->zeichnen();
                                }else hauptfenster->information("Hinweis","Sie müssen erst ein Netz anwählen, das verbogen werden kann.");;
};
void _ansicht::beiskalierenmul2(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,nit->objekt()->skalieren(2));
};
void _ansicht::beiskalierendiv2(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,nit->objekt()->skalieren(0.5));
};
void _ansicht::beiloeschennetz(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 delete nit->objekt();
                                 nit->objekt(0);
                                );
                                loeschenschnittliste();
                                hauptfenster->loeschenanwahl();
                                hauptfenster->zeichnen();
};
void _ansicht::beikopierennetz(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 _netz*n=nit->objekt()->duplizieren();
                                 n->einhaengen(hauptfenster->corundwelt->welt);
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beiinvertieren(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                _polygon*pit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 iterierenliste(nit->objekt(),pit,pit->invertieren());
                                 nit->objekt()->aktualisieren();
                                );
                                hauptfenster->zeichnen();
                                
};
void _ansicht::beiverschiebenraster(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nit->objekt()->verschiebenzumraster(hauptfenster->snapping);
                                 nit->objekt()->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beitauschenxy(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nit->objekt()->tauschenxy();
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beitauschenxz(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nit->objekt()->tauschenxz();
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beitauschenyz(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nit->objekt()->tauschenyz();
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beispiegelnx(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nit->objekt()->spiegelnx();
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beispiegelny(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nit->objekt()->spiegelny();
                                );
                                hauptfenster->zeichnen();
};
void _ansicht::beispiegelnz(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nit->objekt()->spiegelnz();
                                );
                                hauptfenster->zeichnen();
};

void _ansicht::beispeichernnetz(_guiereignisdaten*){
								_listenknoten<_netz>*nit;
								
								_welt*nw=new _welt();
								_netz*nn;
								
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,
                                 nn=nit->objekt()->duplizieren();
                                 nn->einhaengen(nw);
                                );
                                
                                 _guidialogdatei*m_fileDialog = new _guidialogdatei(this); 
                                 m_fileDialog->addierenfilter(L"corundwelt (*.bin)", L"*.bin"); 
                                 m_fileDialog->standarderweiterung(L"bin");
                                 if(m_fileDialog->speichern()){
                                  _zeichenkette<char> h=UnicodeToANSI(m_fileDialog->dateiname()).Data();
                                  weltspeichernbinaer(h,nw);
                                  hauptfenster->statusbar->text(2,L"Netze wurden isoliert gespeichert.");
                                 };
                                 delete m_fileDialog;
                                
                                
                                
                                
                                delete nw;
                                
                                hauptfenster->zeichnen();
};



void _ansicht::beibearbeitenvertex(_guiereignisdaten*){
                                if(hauptfenster->anwahlvertexliste.erstes()){
                                 hauptfenster->dyndialog->neusetzen(L"Angewählten Vertex bearbeiten");
                                 hauptfenster->anwahlvertexliste.erstes()->objekt()->einhaengendialog(hauptfenster->dyndialog);
                                 hauptfenster->dyndialog->zeigen();
                                 hauptfenster->zeichnen();
                                };
};
void _ansicht::loeschenschnittliste(){
                                ls.loeschen();
                                lnsit=0;
                                alteschnittpos.setzen(0,0);
};
