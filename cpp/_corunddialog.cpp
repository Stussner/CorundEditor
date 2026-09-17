#include "../hpp/_corunddialog.hpp"


//******************************************************************************************************************************************************************************************************
//                                                             O X Y D D I A L O G
//******************************************************************************************************************************************************************************************************
_corunddialog::_corunddialog(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Allgemein"); 
};
_corunddialog::~_corunddialog(){
};
void _corunddialog::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                for(int i=0;i<4;i++) hauptfenster->ansicht[i]->neuzeichnen();
};
void _corunddialog::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                for(int i=0;i<4;i++) hauptfenster->ansicht[i]->neuzeichnen();
}; 
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G H A R T 
//******************************************************************************************************************************************************************************************************
_dialoghart::_dialoghart(_hauptfenster*hf,_guifenster*parent):_guidialogmodal(L"Hartgecodete Szene laden",parent){
                                hauptfenster=hf;
                                zentrieren(400, 400, false);
                                
                                _guiknopfdruck*button;
                                // OK 
                                button = new _guiknopfdruck(L"OK", this, new _guiereignisCommand<_dialoghart>(this, &_dialoghart::beiok)); 
                                *button += new _guiort<>(1, 1, false); 
                                *button += new _guiort<>(-180, -35); 
                                *button += new _guigroesse<>(80, 25); 
                                button->zeigen(); 
                                    
                                // Abbrechen 
                                button = new _guiknopfdruck(L"Abbrechen", this, new _guiereignisCommand<_dialoghart>(this, &_dialoghart::beiabbruch)); 
                                *button += new _guiort<>(1, 1, false); 
                                *button += new _guiort<>(-90, -35); 
                                *button += new _guigroesse<>(80, 25); 
                                button->zeigen();   
                                
                                
                                
                                listbox=new _guilistbox(this);  
                                
                                *listbox += new _guiort<>(1, 1, true);                             
                                *listbox += new _guigroesse<>(398, 350); 
                                listbox->addierentext(L"Nummer 0");
                                listbox->addierentext(L"Nummer 1");
                                listbox->addierentext(L"Nummer 2");
                                listbox->addierentext(L"Nummer 3");
                                listbox->addierentext(L"Nummer 4");
                                listbox->addierentext(L"Nummer 5");
                                listbox->addierentext(L"Nummer 6");
                                listbox->addierentext(L"Nummer 7");
                                listbox->addierentext(L"Nummer 8");
                                listbox->addierentext(L"Nummer 9");
                                listbox->selektion(0);
                                listbox->zeigen();
                             //   zeigen();
};
_dialoghart::~_dialoghart(){
};
void _dialoghart::beiok(_guiereignisdaten *ep){
                                //_guidialog::knopfok(ep);
                                _hauptfenster*hf=hauptfenster;
                                if(hf->corundwelt){
                                 delete hf->corundwelt;
                                };
                                 verstecken();
                                 hf->statusbar->text(2,L"Welt wird erzeugt. Bitte warten...");
                                 hf->ansicht[0]->grafik->aktivitaet(true);
                                 hf->corundwelt=new _corundwelt(hf->ansicht[0]->grafik,*hf->texturverwaltung,hf->akustik,*hf->tonverwaltung);
                                 switch(listbox->selektion()){
                                  case 0:hf->corundwelt->erzeugenszene0(hf->ansicht[0]->grafik);break;
                                  case 1:hf->corundwelt->erzeugenszene1(hf->ansicht[0]->grafik);break;
                                  case 2:hf->corundwelt->erzeugenszene2(hf->ansicht[0]->grafik);break;
                                  case 3:hf->corundwelt->erzeugenszene3(hf->ansicht[0]->grafik);break;
                                  case 4:hf->corundwelt->erzeugenszene4(hf->ansicht[0]->grafik);break;
                                  case 5:hf->corundwelt->erzeugenszene5(hf->ansicht[0]->grafik);break;
                                  case 6:hf->corundwelt->erzeugenszene6(hf->ansicht[0]->grafik);break;
                                  case 7:hf->corundwelt->erzeugenszene7(hf->ansicht[0]->grafik);break;
                                  case 8:hf->corundwelt->erzeugenszene8(hf->ansicht[0]->grafik);break;
                                  case 9:hf->corundwelt->erzeugenszene9(hf->ansicht[0]->grafik);break;
                                 };
                                 _zeichenkette<char> h="festszene";
                                 char c[16];
                                 _itoa(listbox->selektion(),c,10);
                                 h+=c;
                                 h+=".txt";
                                 hf->corundwelt->speichername=h;
                                 hf->ansicht[0]->neuzeichnen();
                                 hf->ansicht[1]->neuzeichnen();
                                 hf->ansicht[2]->neuzeichnen();
                                 hf->ansicht[3]->neuzeichnen();
                                 hf->texturansicht->aktualisieren();                                
                                 hf->texturansicht->neuzeichnen();                                
                                 hf->statusbar->text(2,L"Welt wurde neu angelegt.");
                                 // for(int i=0;i<4;i++) hf->ansicht[i]->neuzeichnen();
                                 // delete this;
};
void _dialoghart::beiabbruch(_guiereignisdaten *ep){
                                //_guidialog::buttonCancel(ep);
                                verstecken();
                                //delete this;
}; 
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G U M G E B U N G
//******************************************************************************************************************************************************************************************************

_dialogumgebung::_dialogumgebung(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                               
                                
                                gq=new _geometriequader(0,_vektor3<_tg>(-512,-512,-512),_vektor3<_tg>(1024,0,0),_vektor3<_tg>(0,1024,0),_vektor3<_tg>(0,0,1024),0);
                                for(int i=0;i<6;i++) textur[i]=0;
                                aufgehellt=false;
                                zeichnen=false;
                                einhaengendialog(this);
                                 verstecken();
};
_dialogumgebung::~_dialogumgebung(){
                                delete gq;
};
void _dialogumgebung::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogumgebung::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogumgebung::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 for(int i=0;i<6;i++) if(textur[i]==0) textur[i]=hauptfenster->corundwelt->textur[3];
                                 gq->standardtextur(textur[0]);
                                 _netz*mg=gq->erzeugen();
                                 mg->einhaengen(hauptfenster->corundwelt->welt);
                                 mg->subtraktiv(true);
                                 mg->keinbsp(false);
                                 mg->lightmapschattierung(true);
                                 mg->schattenvolumen(false);
                                 mg->transparenzfaktor(0);
                                 mg->transparenz(false);                                                                
                                 mg->verwendentextur(true);
                                 mg->dynamischschattierend(false);        
                                 if(aufgehellt) mg->aufgehellt(true);                         
                                 if(zeichnen==false) mg->zeichnenflaeche(false);
                                 _polygon*pit;
                                 if(mg->anfang(pit)){
                                  pit->textur(textur[0]);pit=pit->naechstes();
                                  pit->textur(textur[1]);pit=pit->naechstes();
                                  pit->textur(textur[2]);pit=pit->naechstes();
                                  pit->textur(textur[3]);pit=pit->naechstes();
                                  pit->textur(textur[4]);pit=pit->naechstes();
                                  pit->textur(textur[5]);
                                 };
                                 hauptfenster->zeichnen();
                                };
};
void _dialogumgebung::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                neusetzen(L"Umgebung erzeugen");
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                einhaengen(L"Konstruktionsparameter",L"Position",gq->ort());
                                _tg bx,by,bz;
                                bx=gq->vektor(0).laenge();
                                by=gq->vektor(1).laenge();
                                bz=gq->vektor(2).laenge();
                                einhaengen(L"Konstruktionsparameter",L"Breite x",bx);
                                einhaengen(L"Konstruktionsparameter",L"Breite y",by);
                                einhaengen(L"Konstruktionsparameter",L"Breite z",bz);
                                einhaengen(L"Konstruktionsparameter",L"Aufgehellt",aufgehellt);
                                einhaengen(L"Konstruktionsparameter",L"Zeichnen",zeichnen);
};
void _dialogumgebung::auslesendialog(_dynamischerdialog*d){
                                _vektor3<_tg> ort;
                                auslesen(L"Konstruktionsparameter",L"Position",ort);
                                gq->ort(ort);
                                _tg bx,by,bz;
                                auslesen(L"Konstruktionsparameter",L"Breite x",bx);
                                auslesen(L"Konstruktionsparameter",L"Breite y",by);
                                auslesen(L"Konstruktionsparameter",L"Breite z",bz);
                                gq->vektor(_vektor3<_tg>(bx,0,0),_vektor3<_tg>(0,by,0),_vektor3<_tg>(0,0,bz));
                                
                                auslesen(L"Konstruktionsparameter",L"Aufgehellt",aufgehellt);
                                auslesen(L"Konstruktionsparameter",L"Zeichnen",zeichnen);
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G T E X T U R G E O M E T R I E
//******************************************************************************************************************************************************************************************************
_dialogtexturgeometrie::_dialogtexturgeometrie(_hauptfenster*hf,_guifenster*parent):_guidialogmodal(L"Texturgeometrie modifizieren (benutzt Anwahl)",parent){
                                hauptfenster=hf;
                                zentrieren(400, 400, false);
                                *this += new _guiereignisClose<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beiok);
                                _guiknopfdruck*button;
                                // OK 
                                button = new _guiknopfdruck(L"OK", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beiok)); 
                                *button += new _guiort<>(0, 380); 
                                *button += new _guigroesse<>(400, 20); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Hoch", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beihoch)); 
                                *button += new _guiort<>(180,20); 
                                *button += new _guigroesse<>(40, 40); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Runter", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beirunter)); 
                                *button += new _guiort<>(180,100); 
                                *button += new _guigroesse<>(40, 40); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Links", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beilinks)); 
                                *button += new _guiort<>(140,60); 
                                *button += new _guigroesse<>(40, 40); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Rechts", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beirechts)); 
                                *button += new _guiort<>(220,60); 
                                *button += new _guigroesse<>(40, 40); 
                                button->zeigen(); 
                                
                                button = new _guiknopfdruck(L"Drehlinks", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beidrehenlinks)); 
                                *button += new _guiort<>(40,60); 
                                *button += new _guigroesse<>(60, 40); 
                                button->zeigen(); 
                                
                                button = new _guiknopfdruck(L"Drehrechts", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beidrehenrechts)); 
                                *button += new _guiort<>(300,60); 
                                *button += new _guigroesse<>(60, 40); 
                                button->zeigen(); 
                                
                                
                                rasterx=new _guitextfeld(L"8",this);
                                
                                *rasterx += new _guiort<>(200,160); 
                                *rasterx += new _guigroesse<>(200, 20); 
                                *rasterx += new _guiereignisKeyDown<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beitaste);
                                rasterx->zeigen();

                                rastery=new _guitextfeld(L"8",this);
                                *rastery += new _guiort<>(200,180); 
                                *rastery += new _guigroesse<>(200, 20); 
                                *rastery += new _guiereignisKeyDown<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beitaste);
                                rastery->zeigen();

                                skalierungx=new _guitextfeld(L"1.0",this);
                                *skalierungx += new _guiort<>(200,200); 
                                *skalierungx += new _guigroesse<>(200, 20); 
                                *skalierungx += new _guiereignisKeyDown<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beitaste);
                                skalierungx->zeigen();
                                
                                button = new _guiknopfdruck(L"/2", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beiskalierungxdiv2)); 
                                *button += new _guiort<>(160,200); 
                                *button += new _guigroesse<>(20,20); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"*2", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beiskalierungxmul2)); 
                                *button += new _guiort<>(180,200); 
                                *button += new _guigroesse<>(20,20); 
                                button->zeigen(); 
                                
                                

                                skalierungy=new _guitextfeld(L"1.0",this);
                                *skalierungy += new _guiort<>(200,220); 
                                *skalierungy += new _guigroesse<>(200, 20); 
                                *skalierungy += new _guiereignisKeyDown<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beitaste);
                                skalierungy->zeigen();
                                
                                button = new _guiknopfdruck(L"/2", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beiskalierungydiv2)); 
                                *button += new _guiort<>(160,220); 
                                *button += new _guigroesse<>(20,20); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"*2", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beiskalierungymul2)); 
                                *button += new _guiort<>(180,220); 
                                *button += new _guigroesse<>(20,20); 
                                button->zeigen(); 
                                


                                rasterw=new _guitextfeld(L"1.0",this);
                                *rasterw += new _guiort<>(200,240); 
                                *rasterw += new _guigroesse<>(200, 20); 
                                *rasterw += new _guiereignisKeyDown<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beitaste);
                                rasterw->zeigen();

                                
                                _guifensterstatischlinks*sw;
                                
                                sw = new _guifensterstatischlinks(L"Raster x reziprok", this); 
                                *sw += new _guiort<>(10, 160); 
                                *sw += new _guigroesse<>(100, 20); 
                                sw->zeigen();

                                sw = new _guifensterstatischlinks(L"Raster y reziprok", this); 
                                *sw += new _guiort<>(10, 180); 
                                *sw += new _guigroesse<>(100, 20); 
                                sw->zeigen();

                                sw = new _guifensterstatischlinks(L"Skalierung x", this); 
                                *sw += new _guiort<>(10, 200); 
                                *sw += new _guigroesse<>(100, 20); 
                                sw->zeigen();

                                sw = new _guifensterstatischlinks(L"Skalierung y", this); 
                                *sw += new _guiort<>(10, 220); 
                                *sw += new _guigroesse<>(100, 20); 
                                sw->zeigen();

                                sw = new _guifensterstatischlinks(L"Raster Winkel", this); 
                                *sw += new _guiort<>(10, 240); 
                                *sw += new _guigroesse<>(100, 20); 
                                sw->zeigen();

                                button = new _guiknopfdruck(L"Vertikal spiegeln", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beispiegelnvertikal)); 
                                *button += new _guiort<>(0,260); 
                                *button += new _guigroesse<>(400, 20); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Horizontal spiegeln", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beispiegelnhorizontal)); 
                                *button += new _guiort<>(0,280); 
                                *button += new _guigroesse<>(400, 20); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Drehen um 90°", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beidrehen90)); 
                                *button += new _guiort<>(0,300); 
                                *button += new _guigroesse<>(400, 20); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Neusetzen normalisiert", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beineusetzennormalisiert)); 
                                *button += new _guiort<>(0,320); 
                                *button += new _guigroesse<>(400, 20); 
                                button->zeigen(); 
                                button = new _guiknopfdruck(L"Neusetzen skaliert", this, new _guiereignisCommand<_dialogtexturgeometrie>(this, &_dialogtexturgeometrie::beineusetzenskaliert)); 
                                *button += new _guiort<>(0,340); 
                                *button += new _guigroesse<>(400, 20); 
                                button->zeigen(); 

};
_dialogtexturgeometrie::~_dialogtexturgeometrie(){
};
void _dialogtexturgeometrie::beiok(_guiereignisdaten *){
                                verstecken();
};
void _dialogtexturgeometrie::beitaste(_guiereignisdaten *ep){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 _vektor2<_tg> v;
                                 _guitextfeld*eb=dynamic_cast<_guitextfeld*>(ep->fenster);
                                 if(eb){
                                  if(VK_RETURN == ep->wParam){
                                   if(eb==skalierungx) {
                                    v.setzen(skalierungx->zutg(),1);
                                    p->skalierentexturkoordinaten(v,0); 
                                    p->aktualisieren();
                                   };
                                   if(eb==skalierungy) {
                                    v.setzen(1,skalierungy->zutg());
                                    p->skalierentexturkoordinaten(v,0); 
                                    p->aktualisieren();
                                   };
                                  };
                                 };
                                );
                                hauptfenster->zeichnen();
};

void _dialogtexturgeometrie::skalieren(_vektor2<_tg> v){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 p->skalierentexturkoordinaten(v,0); 
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beiskalierungxdiv2(_guiereignisdaten *ep){
                                 _vektor2<_tg> v;
                                 v.setzen(0.5,1);
                                 skalieren(v);
};
void _dialogtexturgeometrie::beiskalierungxmul2(_guiereignisdaten *ep){
                                 _vektor2<_tg> v;
                                 v.setzen(2,1);
                                 skalieren(v);
};
void _dialogtexturgeometrie::beiskalierungydiv2(_guiereignisdaten *ep){
                                 _vektor2<_tg> v;
                                 v.setzen(1,0.5);
                                 skalieren(v);
};
void _dialogtexturgeometrie::beiskalierungymul2(_guiereignisdaten *ep){
                                 _vektor2<_tg> v;
                                 v.setzen(1,2);
                                 skalieren(v);
};


void _dialogtexturgeometrie::beihoch(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 _tg d=rastery->zutg(); 
                                 if(d<=0) d=1;
                                 _vektor2<_tg> v(0,-1.0f/d);
                                 p->verschiebentexturkoordinaten(v,0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
                                
};
void _dialogtexturgeometrie::beirunter(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 _tg d=rastery->zutg(); 
                                 if(d<=0) d=1;
                                 _vektor2<_tg> v(0,1.0f/d);
                                 p->verschiebentexturkoordinaten(v,0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beilinks(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 _tg d=rasterx->zutg(); 
                                 if(d<=0) d=1;
                                 _vektor2<_tg> v(1.0f/d,0);
                                 p->verschiebentexturkoordinaten(v,0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beirechts(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 _tg d=rasterx->zutg(); 
                                 if(d<=0) d=1;
                                 _vektor2<_tg> v(-1.0f/d,0);
                                 p->verschiebentexturkoordinaten(v,0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beispiegelnvertikal(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 p->spiegelntexturkoordinatenx(0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beispiegelnhorizontal(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 p->spiegelntexturkoordinateny(0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beidrehenlinks(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 _tg d=rasterw->zutg(); 
                                 p->rotierentexturkoordinaten(d,0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beidrehenrechts(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 _tg d=rasterw->zutg(); 
                                 p->rotierentexturkoordinaten(-d,0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beidrehen90(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 p->rotierentexturkoordinaten(90,0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beineusetzennormalisiert(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 p->neusetzentexturkoordinatennormalisiert(0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};
void _dialogtexturgeometrie::beineusetzenskaliert(_guiereignisdaten *){
								_listenknoten<_polygon>*lp;
								_polygon*p;
								iterierenliste((&hauptfenster->anwahlpolygonliste),lp,
                                 p=lp->objekt();
                                 p->neusetzentexturkoordinatenskaliert(0);
                                 p->aktualisieren();
                                );
                                hauptfenster->zeichnen();
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G K U G E L
//******************************************************************************************************************************************************************************************************

_dialogkugel::_dialogkugel(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                ort.setzen(0,0,0);
                                vektor.setzen(0,0,0);
                                radius=0.2;
                                farbe.setzen(0.5,0.5,0.5,1);
                                ladung=0;
                                gravitation=0;
                                steuerung=false;
                                augenmodus=false;
                                killer=false;
                                chaotischervektor=false;
                                chaotischerfaktor=0.02;
                                spieler=false;
                                zumspielervektor=false;
                                
                                einhaengendialog(this);
};
_dialogkugel::~_dialogkugel(){
};
void _dialogkugel::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogkugel::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogkugel::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _corundkugel*ok=new _corundkugel(hauptfenster->corundwelt,ort,vektor,radius,farbe);
                                 ok->ladung=ladung;
                                 ok->gravitation=gravitation;
                                 ok->steuerung=steuerung;
                                 ok->augenmodus=augenmodus;
                                 ok->killer=killer;
                                 ok->chaotischervektor=chaotischervektor;
                                 ok->chaotischerfaktor=chaotischerfaktor;
                                 ok->zumspielervektor=zumspielervektor;
                                 if(hauptfenster->corundwelt){
                                  if(spieler) hauptfenster->corundwelt->spieler=ok;
                                 };
                                 hauptfenster->zeichnen();
                                };
};
void _dialogkugel::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Position",ort);
                                new _editionskopplungort(this,L"Konstruktionsparameter",L"Position");
                                einhaengen(L"Konstruktionsparameter",L"Geschwindigkeit",vektor);
                                einhaengen(L"Konstruktionsparameter",L"Radius",radius);
                                einhaengen(L"Konstruktionsparameter",L"Farbe",farbe);
                                einhaengen(L"Konstruktionsparameter",L"Diese Kugel ist Spieler",spieler);
                                einhaengen(L"Konstruktionsparameter",L"elektrische Ladung",ladung);
                                einhaengen(L"Konstruktionsparameter",L"Eigengravitation",gravitation);
                                einhaengen(L"Konstruktionsparameter",L"Steuerung",steuerung);
                                einhaengen(L"Konstruktionsparameter",L"Augenmodus",augenmodus);
                                einhaengen(L"Konstruktionsparameter",L"Tödlich",killer);
                                einhaengen(L"Konstruktionsparameter",L"Chaotisch",chaotischervektor);
                                einhaengen(L"Konstruktionsparameter",L"Chaotischer Faktor",chaotischerfaktor);
                                einhaengen(L"Konstruktionsparameter",L"Vektor zum Spieler",zumspielervektor);
                                
};
void _dialogkugel::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Position",ort);
                                auslesen(L"Konstruktionsparameter",L"Geschwindigkeit",vektor);
                                auslesen(L"Konstruktionsparameter",L"Radius",radius);
                                auslesen(L"Konstruktionsparameter",L"Farbe",farbe);
                                auslesen(L"Konstruktionsparameter",L"Diese Kugel ist Spieler",spieler);
                                auslesen(L"Konstruktionsparameter",L"elektrische Ladung",ladung);
                                auslesen(L"Konstruktionsparameter",L"Eigengravitation",gravitation);
                                auslesen(L"Konstruktionsparameter",L"Steuerung",steuerung);
                                auslesen(L"Konstruktionsparameter",L"Augenmodus",augenmodus);
                                auslesen(L"Konstruktionsparameter",L"Tödlich",killer);
                                auslesen(L"Konstruktionsparameter",L"Chaotisch",chaotischervektor);
                                auslesen(L"Konstruktionsparameter",L"Chaotischer Faktor",chaotischerfaktor);
                                auslesen(L"Konstruktionsparameter",L"Vektor zum Spieler",zumspielervektor);
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G S P I N N E
//******************************************************************************************************************************************************************************************************

_dialogspinne::_dialogspinne(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                ort.setzen(0,0,0);
                                einhaengendialog(this);
};
_dialogspinne::~_dialogspinne(){
};
void _dialogspinne::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogspinne::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogspinne::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _corundspinne*ok=new _corundspinne(hauptfenster->corundwelt,ort);
                                 hauptfenster->zeichnen();
                                };
};
void _dialogspinne::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Position",ort);
                                
};
void _dialogspinne::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Position",ort);
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G L I C H T
//******************************************************************************************************************************************************************************************************
_dialoglicht::_dialoglicht(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                
                                plocus.setzen(0,0,0);
                                pstatisch=false;
                                pdynamisch=true;
                                pdynamischadditiv=true;
                                pschattenvolumen=true;
                                pcolor.setzen(1,1,1);
                                pfarbereflektion.setzen(1,1,1);
                                pintensity=100;
                                einhaengendialog(this);
};
_dialoglicht::~_dialoglicht(){
};
void _dialoglicht::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialoglicht::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialoglicht::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 //_licht<_tg,_to>*l=new _licht<_tg,_to>(hauptfenster->corundwelt->welt,plocus,pcolor,pintensity);
                                 _corundlicht*l=new _corundlicht(hauptfenster->corundwelt,hauptfenster->corundwelt->welt,plocus,pcolor,pintensity);
                                 l->schattenvolumen(pschattenvolumen);
                                 l->statisch(pstatisch);
                                 l->dynamisch(pdynamisch);
                                 l->dynamischadditiv(pdynamischadditiv);
                                 l->farbeglanz(pfarbereflektion);
                                 hauptfenster->zeichnen();
                                };
};
void _dialoglicht::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Position",plocus);
                                new _editionskopplungort(this,L"Konstruktionsparameter",L"Position");
                                einhaengen(L"Konstruktionsparameter",L"Schattenvolumen",pschattenvolumen);
                                einhaengen(L"Konstruktionsparameter",L"Statisch",pstatisch);
                                einhaengen(L"Konstruktionsparameter",L"Dynamisch",pdynamisch);
                                einhaengen(L"Konstruktionsparameter",L"Dynamisch Additiv",pdynamischadditiv);
                                einhaengen(L"Konstruktionsparameter",L"Farbe",pcolor);
                                einhaengen(L"Konstruktionsparameter",L"Farbe Glanz",pfarbereflektion);
                                einhaengen(L"Konstruktionsparameter",L"Intensitaet",pintensity);
                                
};
void _dialoglicht::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Position",plocus);
                                auslesen(L"Konstruktionsparameter",L"Schattenvolumen",pschattenvolumen);
                                auslesen(L"Konstruktionsparameter",L"Statisch",pstatisch);
                                auslesen(L"Konstruktionsparameter",L"Dynamisch",pdynamisch);
                                auslesen(L"Konstruktionsparameter",L"Dynamisch Additiv",pdynamischadditiv);
                                auslesen(L"Konstruktionsparameter",L"Farbe",pcolor);
                                auslesen(L"Konstruktionsparameter",L"Farbe Glanz",pfarbereflektion);
                                auslesen(L"Konstruktionsparameter",L"Intensitaet",pintensity);
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G B I E g E N
//******************************************************************************************************************************************************************************************************
_dialogbiegen::_dialogbiegen(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                port.setzen(0,0,0);
                                protaxis.setzen(0,0,1);
                                pwaxis.setzen(1,0,0);
                                pwinkel=10;
                                einhaengendialog(this);
};
_dialogbiegen::~_dialogbiegen(){
};
void _dialogbiegen::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogbiegen::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogbiegen::erzeugen(){
                                if(hauptfenster->corundwelt){      
                                 _listenknoten<_netz>*nit;
                                 iterierenliste(&hauptfenster->anwahlnetzliste,nit,nit->objekt()->biegen(port,protaxis,pwaxis,pwinkel));
                                 hauptfenster->zeichnen();
                                };
};
void _dialogbiegen::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",port);
                                _editionskopplungort*eo=new _editionskopplungort(this,L"Konstruktionsparameter",L"Ort");
                                einhaengen(L"Konstruktionsparameter",L"Rotationsvektor",protaxis);
                                new _editionskopplungvektor(this,L"Konstruktionsparameter",L"Rotationsvektor",eo);
                                einhaengen(L"Konstruktionsparameter",L"Ebenevektor",pwaxis);
                                new _editionskopplungvektor(this,L"Konstruktionsparameter",L"Ebenevektor",eo);
                                einhaengen(L"Konstruktionsparameter",L"Winkel (degrad)",pwinkel);
                                
};
void _dialogbiegen::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Ort",port);
                                auslesen(L"Konstruktionsparameter",L"Rotationsvektor",protaxis);
                                auslesen(L"Konstruktionsparameter",L"Ebenevektor",pwaxis);
                                auslesen(L"Konstruktionsparameter",L"Winkel (degrad)",pwinkel);

};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G R O T I E R E N
//******************************************************************************************************************************************************************************************************
_dialogrotieren::_dialogrotieren(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                port.setzen(0,0,0);
                                protaxis.setzen(0,0,1);
                                pwinkel=10;
                                einhaengendialog(this);
};
_dialogrotieren::~_dialogrotieren(){
};
void _dialogrotieren::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogrotieren::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogrotieren::erzeugen(){
                                if(hauptfenster->corundwelt){      
                                 _listenknoten<_netz>*nit;
                                 iterierenliste(&hauptfenster->anwahlnetzliste,nit,nit->objekt()->rotieren(port,protaxis,pwinkel));
                                 hauptfenster->zeichnen();
                                };
};
void _dialogrotieren::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",port);
                                _editionskopplungort*eo=new _editionskopplungort(this,L"Konstruktionsparameter",L"Ort");
                                einhaengen(L"Konstruktionsparameter",L"Rotationsachse",protaxis);
                                new _editionskopplungvektor(this,L"Konstruktionsparameter",L"Rotationsachse",eo);
                                einhaengen(L"Konstruktionsparameter",L"Winkel (degrad)",pwinkel);
                                
};
void _dialogrotieren::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Ort",port);
                                auslesen(L"Konstruktionsparameter",L"Rotationsachse",protaxis);
                                auslesen(L"Konstruktionsparameter",L"Winkel (degrad)",pwinkel);

};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G V E R D R E H E N 
//******************************************************************************************************************************************************************************************************
_dialogverdrehen::_dialogverdrehen(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                port.setzen(0,0,0);
                                protaxis.setzen(0,0,1);
                                pwinkel=10;
                                
                                einhaengendialog(this);
};
_dialogverdrehen::~_dialogverdrehen(){
};
void _dialogverdrehen::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogverdrehen::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogverdrehen::erzeugen(){
                                if(hauptfenster->corundwelt){      
                                 _listenknoten<_netz>*nit;
                                 iterierenliste(&hauptfenster->anwahlnetzliste,nit,nit->objekt()->verdrehen(port,protaxis,pwinkel));
                                 hauptfenster->zeichnen();
                                };
};
void _dialogverdrehen::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",port);
                                _editionskopplungort*eo=new _editionskopplungort(this,L"Konstruktionsparameter",L"Ort");
                                einhaengen(L"Konstruktionsparameter",L"Rotationsachse",protaxis);
                                new _editionskopplungvektor(this,L"Konstruktionsparameter",L"Rotationsachse",eo);
                                einhaengen(L"Konstruktionsparameter",L"Winkel (degrad)",pwinkel);
                                
};
void _dialogverdrehen::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Ort",port);
                                auslesen(L"Konstruktionsparameter",L"Rotationsachse",protaxis);
                                auslesen(L"Konstruktionsparameter",L"Winkel (degrad)",pwinkel);

};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G G R A V I T A T I O N 
//******************************************************************************************************************************************************************************************************
_dialoggravitation::_dialoggravitation(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                port.setzen(0,0,0);
                                phomogen.setzen(0,-0.006,0);
                                einhaengendialog(this);
};
_dialoggravitation::~_dialoggravitation(){
};
void _dialoggravitation::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialoggravitation::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialoggravitation::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _gravitation<_tg>*g=new _gravitation<_tg>(hauptfenster->corundwelt->welt,port,phomogen);
                                 hauptfenster->zeichnen();
                                };
};
void _dialoggravitation::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Position",port);
                                einhaengen(L"Konstruktionsparameter",L"Homogenes Feld",phomogen);
                                
};
void _dialoggravitation::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Position",port);
                                auslesen(L"Konstruktionsparameter",L"Homogenes Feld",phomogen);
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F E L D E L E K R T R O S T A T I S C H 
//******************************************************************************************************************************************************************************************************
_dialogfeldelektrostatisch::_dialogfeldelektrostatisch(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                port.setzen(0,0,0);
                                phomogen.setzen(0.01,0,0);
                                einhaengendialog(this);
};
_dialogfeldelektrostatisch::~_dialogfeldelektrostatisch(){
};
void _dialogfeldelektrostatisch::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogfeldelektrostatisch::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogfeldelektrostatisch::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _feldelektrostatisch<_tg>*g=new _feldelektrostatisch<_tg>(hauptfenster->corundwelt->welt,port,phomogen);
                                 hauptfenster->zeichnen();
                                };
};
void _dialogfeldelektrostatisch::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Position",port);
                                einhaengen(L"Konstruktionsparameter",L"Homogenes Feld",phomogen);
};
void _dialogfeldelektrostatisch::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Position",port);
                                auslesen(L"Konstruktionsparameter",L"Homogenes Feld",phomogen);
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F E L D M A G N E T O S T A T I S C H 
//******************************************************************************************************************************************************************************************************
_dialogfeldmagnetostatisch::_dialogfeldmagnetostatisch(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                port.setzen(0,0,0);
                                phomogen.setzen(0.01,0,0);
                                einhaengendialog(this);
};
_dialogfeldmagnetostatisch::~_dialogfeldmagnetostatisch(){
};
void _dialogfeldmagnetostatisch::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogfeldmagnetostatisch::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogfeldmagnetostatisch::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _feldmagnetostatisch<_tg>*g=new _feldmagnetostatisch<_tg>(hauptfenster->corundwelt->welt,port,phomogen);
                                 hauptfenster->zeichnen();
                                };
};
void _dialogfeldmagnetostatisch::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Position",port);
                                einhaengen(L"Konstruktionsparameter",L"Homogenes Feld",phomogen);
};
void _dialogfeldmagnetostatisch::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Position",port);
                                auslesen(L"Konstruktionsparameter",L"Homogenes Feld",phomogen);
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G P A R T I K E L Q U E L L E 
//******************************************************************************************************************************************************************************************************
_dialogpartikelquellesprite::_dialogpartikelquellesprite(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                port.setzen(0,1,0);
                                pvektor.setzen(0,1,0);
                                
                                

                                einhaengendialog(this);
};
_dialogpartikelquellesprite::~_dialogpartikelquellesprite(){
};
void _dialogpartikelquellesprite::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogpartikelquellesprite::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogpartikelquellesprite::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _partikelquellesprite*g=new _partikelquellesprite(hauptfenster->corundwelt->welt,hauptfenster->corundwelt->welt,hauptfenster->corundwelt->welt,hauptfenster->corundwelt->pzeit,port,pvektor,10,hauptfenster->texturansicht->anwahl());
                                 hauptfenster->zeichnen();
                                };
};
void _dialogpartikelquellesprite::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",port);
                                einhaengen(L"Konstruktionsparameter",L"Vektor",pvektor);
                                
};
void _dialogpartikelquellesprite::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Ort",port);
                                auslesen(L"Konstruktionsparameter",L"Vektor",pvektor);
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G N E T Z W A H L 
//******************************************************************************************************************************************************************************************************
_dialognetzwahl::_dialognetzwahl(_hauptfenster*hf,_guifenster*parent):_guidialog(L"Netzwahl treffen",parent){
                                hauptfenster=hf;
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=0;
                                pcorundfigur=0;
                                pindex=0;
                                erzeugen(WS_CAPTION| WS_BORDER);
                                zentrieren(120, 40, false);
                                *this += new _guiereignisClose<_dialognetzwahl>(this, &_dialognetzwahl::beiok);                                
                                _guiknopfdruck*button;
                                // OK 
                                button = new _guiknopfdruck(L"Netz wählen", this, new _guiereignisCommand<_dialognetzwahl>(this, &_dialognetzwahl::beiok)); 
                                *button += new _guiort<>(0, 0,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 
                                // Abbruch
                                button = new _guiknopfdruck(L"Abbruch", this, new _guiereignisCommand<_dialognetzwahl>(this, &_dialognetzwahl::beiabbruch)); 
                                *button += new _guiort<>(0, 0.5,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 

};                                
_dialognetzwahl::~_dialognetzwahl(){
};
void _dialognetzwahl::index(const int i){
                                pindex=i;
};
int _dialognetzwahl::index()const{
                                return(pindex);
};
void _dialognetzwahl::corundstein(_corundstein*os){
                                pcorundobjekt=0;
                                pcorundboden=0;                                
                                pcorundstein=os;
                                pcorundfigur=0;
};
void _dialognetzwahl::corundobjekt(_corundobjekt*os){
                                pcorundstein=0;
                                pcorundboden=0;                                
                                pcorundobjekt=os;
                                pcorundfigur=0;
};
void _dialognetzwahl::corundboden(_corundboden*os){
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=os;
                                pcorundfigur=0;
};
void _dialognetzwahl::corundfigur(_corundfigur*os){
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=0;
                                pcorundfigur=os;
};
void _dialognetzwahl::beiok(_guiereignisdaten *){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 _netz*n=hauptfenster->anwahlnetzliste.erstes()->objekt();
                                 if (pcorundstein) pcorundstein->netzwahl(n,pindex);
                                 if (pcorundobjekt) pcorundobjekt->netzwahl(n,pindex);
                                 if (pcorundboden) pcorundboden->netzwahl(n,pindex);
                                 if (pcorundfigur) pcorundfigur->netzwahl(n,pindex);
                                 verstecken();
                                }else hauptfenster->information("Hinweis","Wählen Sie ein Netz aus und drücken dann die Schaltfläche.");
};                    

void _dialognetzwahl::beiabbruch(_guiereignisdaten *){
                                verstecken();
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G K N O T E N W A H L 
//******************************************************************************************************************************************************************************************************
_dialogknotenwahl::_dialogknotenwahl(_hauptfenster*hf,_guifenster*parent):_guidialog(L"knotenwahl treffen",parent){
                                hauptfenster=hf;
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=0;
                                pcorundfigur=0;
                                pindex=0;
                                erzeugen(WS_CAPTION| WS_BORDER);
                                zentrieren(120, 40, false);
                                *this += new _guiereignisClose<_dialogknotenwahl>(this, &_dialogknotenwahl::beiok);                                
                                _guiknopfdruck*button;
                                // OK 
                                button = new _guiknopfdruck(L"knoten wählen", this, new _guiereignisCommand<_dialogknotenwahl>(this, &_dialogknotenwahl::beiok)); 
                                *button += new _guiort<>(0, 0,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 
                                // Abbruch
                                button = new _guiknopfdruck(L"Abbruch", this, new _guiereignisCommand<_dialogknotenwahl>(this, &_dialogknotenwahl::beiabbruch)); 
                                *button += new _guiort<>(0, 0.5,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 

};                                
_dialogknotenwahl::~_dialogknotenwahl(){
};
void _dialogknotenwahl::index(const int i){
                                pindex=i;
};
int _dialogknotenwahl::index()const{
                                return(pindex);
};
void _dialogknotenwahl::corundstein(_corundstein*os){
                                pcorundobjekt=0;
                                pcorundboden=0;                                
                                pcorundstein=os;
                                pcorundfigur=0;
};
void _dialogknotenwahl::corundobjekt(_corundobjekt*os){
                                pcorundstein=0;
                                pcorundboden=0;                                
                                pcorundobjekt=os;
                                pcorundfigur=0;
};
void _dialogknotenwahl::corundboden(_corundboden*os){
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=os;
                                pcorundfigur=0;
};
void _dialogknotenwahl::corundfigur(_corundfigur*os){
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=0;
                                pcorundfigur=os;
};
void _dialogknotenwahl::beiok(_guiereignisdaten *){
                                if(hauptfenster->anwahlknoten){
                                 if (pcorundstein) pcorundstein->knotenwahl(hauptfenster->anwahlknoten,pindex);
                                 if (pcorundobjekt) pcorundobjekt->knotenwahl(hauptfenster->anwahlknoten,pindex);
                                 if (pcorundboden) pcorundboden->knotenwahl(hauptfenster->anwahlknoten,pindex);
                                 if (pcorundfigur) pcorundfigur->knotenwahl(hauptfenster->anwahlknoten,pindex);
                                 verstecken();
                                }else hauptfenster->information("Hinweis","Wählen Sie einen Knoten aus und drücken dann die Schaltfläche.");
};                    

void _dialogknotenwahl::beiabbruch(_guiereignisdaten *){
                                verstecken();
}; 
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F I G U R W A H L 
//******************************************************************************************************************************************************************************************************
_dialogfigurwahl::_dialogfigurwahl(_hauptfenster*hf,_guifenster*parent):_guidialog(L"Figurwahl treffen",parent){
                                hauptfenster=hf;
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=0;
                                pcorundfigur=0;
                                pindex=0;
                                erzeugen(WS_CAPTION| WS_BORDER);
                                zentrieren(120, 40, false);
                                *this += new _guiereignisClose<_dialogfigurwahl>(this, &_dialogfigurwahl::beiok);                                
                                _guiknopfdruck*button;
                                // OK 
                                button = new _guiknopfdruck(L"Figur wählen", this, new _guiereignisCommand<_dialogfigurwahl>(this, &_dialogfigurwahl::beiok)); 
                                *button += new _guiort<>(0, 0,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 
                                // Abbruch
                                button = new _guiknopfdruck(L"Abbruch", this, new _guiereignisCommand<_dialogfigurwahl>(this, &_dialogfigurwahl::beiabbruch)); 
                                *button += new _guiort<>(0, 0.5,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 

};                                
_dialogfigurwahl::~_dialogfigurwahl(){
};
void _dialogfigurwahl::index(const int i){
                                pindex=i;
};
int _dialogfigurwahl::index()const{
                                return(pindex);
};
void _dialogfigurwahl::corundstein(_corundstein*os){
                                pcorundobjekt=0;
                                pcorundboden=0;                                
                                pcorundstein=os;
                                pcorundfigur=0;
};
void _dialogfigurwahl::corundobjekt(_corundobjekt*os){
                                pcorundstein=0;
                                pcorundboden=0;                                
                                pcorundobjekt=os;
                                pcorundfigur=0;
};
void _dialogfigurwahl::corundboden(_corundboden*os){
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=os;
                                pcorundfigur=0;
};
void _dialogfigurwahl::corundfigur(_corundfigur*os){
                                pcorundstein=0;
                                pcorundobjekt=0;
                                pcorundboden=0;
                                pcorundfigur=os;
};
void _dialogfigurwahl::beiok(_guiereignisdaten *){
                                if(hauptfenster->anwahlkugel){
                                 _corundfigur*cf=hauptfenster->anwahlkugel;
                                 if (pcorundstein) pcorundstein->figurwahl(cf,pindex);
                                 if (pcorundobjekt) pcorundobjekt->figurwahl(cf,pindex);
                                 if (pcorundboden) pcorundboden->figurwahl(cf,pindex);
                                 if (pcorundfigur) pcorundfigur->figurwahl(cf,pindex);
                                 verstecken();
                                }else hauptfenster->information("Hinweis","Wählen Sie eine Kugel oder ein Skelett (Figur)  aus und drücken dann die Schaltfläche.");
};                    

void _dialogfigurwahl::beiabbruch(_guiereignisdaten *){
                                verstecken();
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G K N O T E N
//******************************************************************************************************************************************************************************************************

_dialogknoten::_dialogknoten(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                plocus.setzen(4,0,4);
                                index=0;
                                vektorankunft.setzen(0,0,0);
                                vektorabfahrt.setzen(0,0,0);
                                wartezeit=100;
                                einhaengendialog(this);
};
_dialogknoten::~_dialogknoten(){
};
void _dialogknoten::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogknoten::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogknoten::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _corundknoten*k=new _corundknoten(hauptfenster->corundwelt,plocus,index);
                                 k->vektorabfahrt=vektorabfahrt;
                                 k->vektorankunft=vektorankunft;
                                 k->wartezeit=wartezeit;
                                 hauptfenster->zeichnen();
                                };
};
void _dialogknoten::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Index",index);
                                einhaengen(L"Konstruktionsparameter",L"Position",plocus);
                                new _editionskopplungort(this,L"Konstruktionsparameter",L"Position");
                                einhaengen(L"Konstruktionsparameter",L"Richtung der Ankunft",vektorankunft);
                                einhaengen(L"Konstruktionsparameter",L"Richtung der Abfahrt",vektorabfahrt);
                                einhaengen(L"Konstruktionsparameter",L"Wartezeit [zyklen]",wartezeit);
                                
};
void _dialogknoten::auslesendialog(_dynamischerdialog*d){
                                auslesen(L"Konstruktionsparameter",L"Index",index);
                                auslesen(L"Konstruktionsparameter",L"Position",plocus);
                                auslesen(L"Konstruktionsparameter",L"Richtung der Ankunft",vektorankunft);
                                auslesen(L"Konstruktionsparameter",L"Richtung der Abfahrt",vektorabfahrt);
                                auslesen(L"Konstruktionsparameter",L"Wartezeit [zyklen]",wartezeit);

};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F R A K T A L 
//******************************************************************************************************************************************************************************************************

_dialogfraktal::_dialogfraktal(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf),fr(0.7,-0.01){
                                hauptfenster=hf;
                                original=0;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                verstecken();
                                plocus.setzen(5,0,5);
                                pe0.setzen(1,0,0);
                                pe1.setzen(0,0,1);
                                pe2.setzen(0,1,0);
                                pschiebrichtung.setzen(0,1,0);
                                einhaengendialog(this);
                                
};
_dialogfraktal::~_dialogfraktal(){
                                if(original) delete original;
                                original=0;
};
void _dialogfraktal::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
void _dialogfraktal::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
void _dialogfraktal::zeigen(){
                                _dynamischerdialog::zeigen();
                                if(original) delete original;
                                original=0;
                                if(hauptfenster->anwahlnetzliste.erstes()) {
                                 _netz*n=hauptfenster->anwahlnetzliste.erstes()->objekt();
                                 original=n->duplizieren();
                                 original->_listenknotenbasis<_netz>::aushaengen();
                                };
};
void _dialogfraktal::verstecken(){
                                _dynamischerdialog::verstecken();
                                if(original) delete original;
                                original=0;
};
void _dialogfraktal::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 if(hauptfenster->anwahlnetzliste.erstes()){
                                  _vektoranalysis3<_tg> va;
                                 
                                  _netz*n=hauptfenster->anwahlnetzliste.erstes()->objekt();
                                  _polygon*pit;
                                  _vertex*vit;
                                  _vektor3<_tg> h;
                                  _tg D=va.determinieren(pe0,pe1,pe2);
                                  if(fabs(D)>nahenull){
                                   n->markierungvertex(1);
                                   if(n->anfang(pit))do{
                                   vit=pit->vertex();
                                    if(vit)do{
                                     if(vit->markierung()==1){
                                      vit->markierung(0);
                                      _tg a=va.determinieren(vit->ort()-plocus,pe1,pe2)/D;
                                      _tg b=va.determinieren(pe0,vit->ort()-plocus,pe2)/D;
                                      _tg d=log(1+fr.berechnen(a,b,100));
                                      vit->ort(vit->ort()+pschiebrichtung*d);
                                     };
                                     vit=vit->naechstes(pit);
                                    }while(vit!=pit->vertex());
                                   }while(n->naechstes(pit));
                                   n->aktualisieren();
                                   hauptfenster->zeichnen();
                                  };
                                 };
                                };
};
void _dialogfraktal::beiknopfruecksetzen(_guiereignisdaten*){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 _netz*n=hauptfenster->anwahlnetzliste.erstes()->objekt();
                                 if(original){
                                  n->_listebasis<_polygon>::loeschen();
                                  n->_listebasis<_netzschatten>::loeschen();
                                  n->_liste<_partition::_sektor>::aushaengen();
                                  _netz*temp=original->duplizieren();
                                  n->vereinigen(temp);
                                  n->aktualisieren();
                                  hauptfenster->zeichnen();
                                 }else{
                                  //hauptfenster->statusbar->text
                                 };
                                };
};
void _dialogfraktal::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Methode [0..27]",fr.methode());
                                einhaengen(L"Konstruktionsparameter",L"Position",plocus);
                                einhaengen(L"Konstruktionsparameter",L"Komplexe Variation : real",fr.real());
                                einhaengen(L"Konstruktionsparameter",L"Komplexe Variation : imagninär",fr.imaginaer());
                                einhaengen(L"Konstruktionsparameter",L"Parameterebenenrichtung 0",pe0);
                                einhaengen(L"Konstruktionsparameter",L"Parameterebenenrichtung 1",pe1);
                                einhaengen(L"Konstruktionsparameter",L"Parameterebenenrichtung 2",pe2);
                                einhaengen(L"Konstruktionsparameter",L"Verschiebungsrichtung",pschiebrichtung);
                                new _editionskopplungort(this,L"Konstruktionsparameter",L"Position");
                                einhaengenknopf<_dialogfraktal>(L"Konstruktionsparameter",L"Netz",L"rücksetzen",this,&_dialogfraktal::beiknopfruecksetzen);
};
void _dialogfraktal::auslesendialog(_dynamischerdialog*d){
                                unsigned int i;
                                auslesen(L"Konstruktionsparameter",L"Methode [0..27]",i);
                                fr.methode(i);
                                auslesen(L"Konstruktionsparameter",L"Position",plocus);
                                auslesen(L"Konstruktionsparameter",L"Komplexe Variation : real",fr.real());
                                auslesen(L"Konstruktionsparameter",L"Komplexe Variation : imagninär",fr.imaginaer());
                                auslesen(L"Konstruktionsparameter",L"Parameterebenenrichtung 0",pe0);
                                auslesen(L"Konstruktionsparameter",L"Parameterebenenrichtung 1",pe1);
                                auslesen(L"Konstruktionsparameter",L"Parameterebenenrichtung 2",pe2);
                                auslesen(L"Konstruktionsparameter",L"Verschiebungsrichtung",pschiebrichtung);
};
