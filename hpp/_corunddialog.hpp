#ifndef _oxyydeditorgeometrie_included
#define _oxyydeditorgeometrie_included

class _corunddialog;
class _dialoghart;
class _dialogumgebung;
class _dialogtexturgeometrie;
template<class T>class _dialoggeometrie;
class _dialogkugel;
class _dialogspinne;
template<class T>class _dialogfigur;
template<class OS> class _dialogstein;
template<class OO> class _dialogobjekt;
template<class OB> class _dialogboden;
class _dialognetzwahl;
class _dialogfigurwahl;
class _dialogknotenwahl;
class _dialoglicht;
class _dialoggravitation;
class _dialogpartikelquellesprite;
class _dialogknoten;
class _dialogfraktal;
class _dialogbiegen;
class _dialogrotieren;
class _dialogverdrehen;

#include "../hpp/_corundeditor.hpp"
//#include <BCGUI/Dialogs/modaldialog.hpp>
//#include <BCGUI/Windows/staticwindow.hpp>
//#include <BCGUI/Controls/listbox.hpp>
#include "../../oxyd/hpp/_corundstein.hpp"
#include "../../oxyd/hpp/_corundfigur.hpp"
#include "../../oxyd/hpp/_corundschalter.hpp"

class _hauptfenster;
class _geometriequader;
class _corundstein;
template<class T>class _corundschalter;

//******************************************************************************************************************************************************************************************************
//                                                             O X Y D D I A L O G
//******************************************************************************************************************************************************************************************************
class _corunddialog:public _dynamischerdialog{
        public:
                _corunddialog(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_corunddialog();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
        private:
                _hauptfenster*hauptfenster;                
               
};

//******************************************************************************************************************************************************************************************************
//                                                            D I A L O G H A R T 
//******************************************************************************************************************************************************************************************************
class _dialoghart:public _guidialogmodal{
        public:
                _dialoghart(_hauptfenster*hf,_guifenster*parent);
                virtual ~_dialoghart();
                void beiok(_guiereignisdaten *); 
                void beiabbruch(_guiereignisdaten *); 
        private:
                _hauptfenster*hauptfenster;    
                _guilistbox*listbox;     
              
               
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G U M G E B U N G
//******************************************************************************************************************************************************************************************************
class _dialogumgebung:public _dynamischerdialog,_editierbar{
        public:
                _dialogumgebung(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogumgebung();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        public:
                _hauptfenster*hauptfenster;  
                _geometriequader*gq;
                _textur<_tb>*textur[6];
                bool aufgehellt;
                bool zeichnen;
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G T E X T U R G E O M E T R I E
//******************************************************************************************************************************************************************************************************
class _dialogtexturgeometrie:public _guidialogmodal{
        public:
                _dialogtexturgeometrie(_hauptfenster*hf,_guifenster*parent);
                virtual ~_dialogtexturgeometrie();
        protected:                
                void beiok(_guiereignisdaten *); 
                void beitaste(_guiereignisdaten *); 
                void beihoch(_guiereignisdaten *);
                void beirunter(_guiereignisdaten *);
                void beilinks(_guiereignisdaten *);
                void beirechts(_guiereignisdaten *);
                void beispiegelnvertikal(_guiereignisdaten *); 
                void beispiegelnhorizontal(_guiereignisdaten *); 
                void beidrehenlinks(_guiereignisdaten *); 
                void beidrehenrechts(_guiereignisdaten *); 
                void beidrehen90(_guiereignisdaten *);
                void beineusetzennormalisiert(_guiereignisdaten *);
                void beineusetzenskaliert(_guiereignisdaten *);
                void beiskalierungxmul2(_guiereignisdaten *);
                void beiskalierungxdiv2(_guiereignisdaten *);
                void beiskalierungymul2(_guiereignisdaten *);
                void beiskalierungydiv2(_guiereignisdaten *);
                void skalieren(_vektor2<_tg> v);
                
        private:
                _hauptfenster*hauptfenster;
                _guitextfeld*rasterx;
                _guitextfeld*rastery;
                _guitextfeld*rasterw;
                _guitextfeld*skalierungx;
                _guitextfeld*skalierungy;
                
};                
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G G E O M E T R I E
//******************************************************************************************************************************************************************************************************
template <class T> 
class _dialoggeometrie:public _dynamischerdialog{
        public:
                _dialoggeometrie(_hauptfenster*hf,T*gq,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialoggeometrie();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
        private:
                _hauptfenster*hauptfenster;  
                T*geometrie;
               
};
template<class T>_dialoggeometrie<T>::_dialoggeometrie(_hauptfenster*hf,T*gq,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                geometrie=gq;
                                addierensektion(L"Konstruktionsparameter"); 
                                verstecken();
 
};
template<class T>_dialoggeometrie<T>::~_dialoggeometrie(){
};
template<class T>void _dialoggeometrie<T>::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
template<class T>void _dialoggeometrie<T>::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
template<class T>void _dialoggeometrie<T>::erzeugen(){
                                if(hauptfenster->corundwelt){                                
                                 _netz*n=geometrie->erzeugen();
                                 n->einhaengen(hauptfenster->corundwelt->welt);
                                 n->keinbsp(true);
                                 n->lightmapschattierung(false);
                                 n->schattenvolumen(true);
                                 hauptfenster->zeichnen();
                                };
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G K U G E L
//******************************************************************************************************************************************************************************************************
class _dialogkugel:public _dynamischerdialog,_editierbar{
        public:
                _dialogkugel(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogkugel();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> ort;
                _vektor3<_tg> vektor;
                _tg radius;
                _vektor4<_to> farbe;
                _tg ladung;
                _tg gravitation;
                bool steuerung;
                bool spieler;
                bool augenmodus;
                bool killer;
                bool chaotischervektor;
                _tg chaotischerfaktor;
                bool zumspielervektor;                
               
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G S P I N N E
//******************************************************************************************************************************************************************************************************
class _dialogspinne:public _dynamischerdialog,_editierbar{
        public:
                _dialogspinne(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogspinne();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> ort;
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F I G U R
//******************************************************************************************************************************************************************************************************
template<class T>class _dialogfigur:public _dynamischerdialog,_editierbar{
        public:
                _dialogfigur(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogfigur();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> ort;
                _vektor3<_tg> richtung;
                _vektor3<_tg> normale;
                _vektor3<_tg> seite;
};
template<class T> _dialogfigur<T>::_dialogfigur(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                zentrieren(400,160);
                                ort.setzen(0,0,0);
                                richtung.setzen(1,0,0);
                                normale.setzen(0,1,0);
                                seite.setzen(0,0,1);
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                einhaengendialog(this);
                                verstecken();
};
template<class T> _dialogfigur<T>::~_dialogfigur(){
};
template<class T> void _dialogfigur<T>::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
template<class T> void _dialogfigur<T>::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
template<class T> void _dialogfigur<T>::erzeugen(){
                                if(hauptfenster->corundwelt){
                                 T*figur=new T(hauptfenster->corundwelt,ort,richtung,normale,seite);
                                 hauptfenster->zeichnen();
                                };
};
template<class T> void _dialogfigur<T>::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",ort);
                                new _editionskopplungort(d,L"Konstruktionsparameter",L"Ort");
                                einhaengen(L"Konstruktionsparameter",L"Richtung",richtung);
                                einhaengen(L"Konstruktionsparameter",L"Normale",normale);
                                einhaengen(L"Konstruktionsparameter",L"Seite",seite);
                                
};
template<class T> void _dialogfigur<T>::auslesendialog(_dynamischerdialog*d){
                               // d->editierbar(this);
                                auslesen(L"Konstruktionsparameter",L"Ort",ort);
                                auslesen(L"Konstruktionsparameter",L"Richtung",richtung);
                                auslesen(L"Konstruktionsparameter",L"Normale",normale);
                                auslesen(L"Konstruktionsparameter",L"Seite",seite);
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G L I C H T
//******************************************************************************************************************************************************************************************************
class _dialoglicht:public _dynamischerdialog,_editierbar{
        public:
                _dialoglicht(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialoglicht();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                bool pstatisch;
                bool pdynamisch;
                bool pdynamischadditiv;
                bool pschattenvolumen;
                _vektor3<_tg> plocus;
                _vektor3<_to> pcolor;
                _vektor3<_to> pfarbereflektion;
                _to pintensity;
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G G R A V I T A T I O N 
//******************************************************************************************************************************************************************************************************
class _dialoggravitation:public _dynamischerdialog,_editierbar{
        public:
                _dialoggravitation(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialoggravitation();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> port;
                _vektor3<_tg> phomogen;
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F E L D E L E K T R O S T A T I S C H 
//******************************************************************************************************************************************************************************************************
class _dialogfeldelektrostatisch:public _dynamischerdialog,_editierbar{
        public:
                _dialogfeldelektrostatisch(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogfeldelektrostatisch();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> port;
                _vektor3<_tg> phomogen;
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F E L D M A G N E T O S T A T I S C H 
//******************************************************************************************************************************************************************************************************
class _dialogfeldmagnetostatisch:public _dynamischerdialog,_editierbar{
        public:
                _dialogfeldmagnetostatisch(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogfeldmagnetostatisch();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> port;
                _vektor3<_tg> phomogen;
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G P A R T I K E L Q U E L L E 
//******************************************************************************************************************************************************************************************************
class _dialogpartikelquellesprite:public _dynamischerdialog,_editierbar{
        public:
                _dialogpartikelquellesprite(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogpartikelquellesprite();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> port;
                _vektor3<_tg> pvektor;
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G S T E I N 
//******************************************************************************************************************************************************************************************************
template<class OS> class _dialogstein:public _dynamischerdialog,_editierbar{
        public:
                _dialogstein(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogstein();
                void netz(_netz*);
                void aktivieren();
                OS*erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> ort;
                _vektor3<_tg> breite;
                bool lightmap;
                _netz*pnetz;
                bool neuesnetz;
               
};

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G S T E I N
//******************************************************************************************************************************************************************************************************
template<class OS> _dialogstein<OS>::_dialogstein(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                zentrieren(400,160);
                                ort.setzen(0,0,0);
                                breite.setzen(1,1,1);
                                lightmap=true;
                                pnetz=0;
                                neuesnetz=false;
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                einhaengendialog(this);
                                verstecken();
};
template<class OS> _dialogstein<OS>::~_dialogstein(){
};
template<class OS> void _dialogstein<OS>::netz(_netz*n){
                                pnetz=n;
                                neuesnetz=true;
};
template<class OS> void _dialogstein<OS>::aktivieren(){
                                
                                OS*os=0;
                                if(hauptfenster->corundwelt){
                                 bool anwahlnutzen=false;
                                 if(hauptfenster->anwahlnetzliste.erstes()){
                                  if(hauptfenster->abfrage("Konstruktion von Steinen","Sie haben ein Netz angewählt. Soll dieses Netz dupliziert werden, um daraus einen Stein zu konstruieren?")){
                                   anwahlnutzen=true;
                                  };
                                 };
                                 if(anwahlnutzen){                                 
                                  //leeren Stein erzeugen und Zuweisung durchführen
                                  os=new OS(hauptfenster->corundwelt);
                                  _netz*n=hauptfenster->anwahlnetzliste.erstes()->objekt()->duplizieren();
                                  os->_netz::subtraktiv(n->subtraktiv());
                                  os->_netz::keinbsp(n->keinbsp());
                                  os->_netz::schattenvolumen(n->schattenvolumen());
                                  os->_netz::schattenvolumenlaenge(n->schattenvolumenlaenge());
                                  os->_netz::brechzahl(n->brechzahl());
                                  os->_netz::dispersionsskalierung(n->dispersionsskalierung());
                                  os->_netz::vereinigen(n);
                                  os->_netz::einhaengen(hauptfenster->corundwelt->welt);
                                  _corundstein*osb=os;//dynamic_cast<_corundstein*>(pnetz);
                                  osb->nachbereitenkonstruktion();
                                  hauptfenster->zeichnen();
                                 }else{
                                  zeigen();
                                 };
                                }else{
                                 hauptfenster->information("Hinweis","Sie müssen erst eine Welt erzeugen, bevor Sie einen Stein konstruieren können.");
                                };
                                
};
template<class OS> void _dialogstein<OS>::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
template<class OS> void _dialogstein<OS>::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
template<class OS> OS* _dialogstein<OS>::erzeugen(){
                                if(hauptfenster->corundwelt){
                                 OS*os=new OS(hauptfenster->corundwelt);
                                 pnetz=os;
                                 if(pnetz){
                                  _geometriequader*gq=new _geometriequader(0,ort,breite[0],breite[1],breite[2],hauptfenster->texturansicht->anwahl());
                                  gq->texturkoordinatenlaenge(breite[0],breite[1],breite[2]);
                                  _netz*n=gq->erzeugen();
                                  delete gq;
                                  pnetz->vereinigen(n);
                                  pnetz->verknuepfenverbindervertexpolygon();
                                  pnetz->einhaengen(hauptfenster->corundwelt->welt);
                                  if(lightmap){
                                   pnetz->anlegentexturkoordinaten(2);
                                   pnetz->lightmaptexelgroesse(1);
                                   pnetz->verwendentexturdynamisch(true);                                  
                                   pnetz->farbeverbinder(_vektor4<_to>(0,0,0,1));
                                  };
                                   _corundstein*osb=os;//dynamic_cast<_corundstein*>(pnetz);
                                   osb->nachbereitenkonstruktion();
                                  hauptfenster->zeichnen();
                                 };
                                 return(os);
                                };
                                return(0);
};
template<class OS> void _dialogstein<OS>::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",ort);
                                new _editionskopplungort(d,L"Konstruktionsparameter",L"Ort");
                                einhaengen(L"Konstruktionsparameter",L"Breite",breite);
                                einhaengen(L"Konstruktionsparameter",L"Lightmap",lightmap);
                                
};
template<class OS> void _dialogstein<OS>::auslesendialog(_dynamischerdialog*d){
                               // d->editierbar(this);
                                auslesen(L"Konstruktionsparameter",L"Ort",ort);
                                auslesen(L"Konstruktionsparameter",L"Breite",breite);
                                auslesen(L"Konstruktionsparameter",L"Lightmap",lightmap);
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G  O B J E K T 
//******************************************************************************************************************************************************************************************************
template<class OO> class _dialogobjekt:public _dynamischerdialog,_editierbar{
        public:
                _dialogobjekt(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogobjekt();
                void aktivieren();
                OO*erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> ort;
               
};
template<class OO> _dialogobjekt<OO>::_dialogobjekt(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                zentrieren(400,160);
                                ort.setzen(0,0,0);
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                einhaengendialog(this);
                                verstecken();
};
template<class OO> _dialogobjekt<OO>::~_dialogobjekt(){
};
template<class OO> void _dialogobjekt<OO>::aktivieren(){
                                OO*OO=0;
                                if(hauptfenster->corundwelt){
                                 zeigen();
                                }else{
                                 hauptfenster->information("Hinweis","Sie müssen erst eine Welt erzeugen, bevor Sie einen objekt konstruieren können.");
                                };
};
template<class OO> void _dialogobjekt<OO>::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
template<class OO> void _dialogobjekt<OO>::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
template<class OO> OO* _dialogobjekt<OO>::erzeugen(){
                                if(hauptfenster->corundwelt){
                                 OO*co=new OO(hauptfenster->corundwelt,ort);
                                 
                                 co->nachbereitenkonstruktion();
                                /* pnetz=OO;
                                 if(pnetz){
                                  _geometriequader*gq=new _geometriequader(0,ort,breite[0],breite[1],breite[2],hauptfenster->texturansicht->anwahl());
                                  gq->texturkoordinatenlaenge(breite[0],breite[1],breite[2]);
                                  _netz*n=gq->erzeugen();
                                  delete gq;
                                  pnetz->vereinigen(n);
                                  pnetz->verknuepfenverbindervertexpolygon();
                                  pnetz->einhaengen(hauptfenster->corundwelt->welt);
                                  if(lightmap){
                                   pnetz->anlegentexturkoordinaten(2);
                                   pnetz->lightmaptexelgroesse(1);
                                   pnetz->verwendentexturdynamisch(true);                                  
                                   pnetz->farbeverbinder(_vektor4<_to>(0,0,0,1));
                                   _corundobjekt*OOb=OO;//dynamic_cast<_corundobjekt*>(pnetz);
                                   OOb->nachbereitenkonstruktion();
                                  };
                                  hauptfenster->zeichnen();
                                 };*/
                                 hauptfenster->zeichnen();
                                 return(co);
                                };
                                return(0);
};
template<class OO> void _dialogobjekt<OO>::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",ort);

                                
};
template<class OO> void _dialogobjekt<OO>::auslesendialog(_dynamischerdialog*d){
                               // d->editierbar(this);
                                auslesen(L"Konstruktionsparameter",L"Ort",ort);

};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G B O D E N 
//******************************************************************************************************************************************************************************************************
template<class OB> class _dialogboden:public _dynamischerdialog,_editierbar{
        public:
                _dialogboden(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogboden();
                void aktivieren();
                OB*erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);                
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> ort;
                _vektor3<_tg> e0;
                _vektor3<_tg> e1;
};
template<class OB> _dialogboden<OB>::_dialogboden(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent):_dynamischerdialog(pn,parent,hf){
                                hauptfenster=hf;
                                zentrieren(400,160);
                                ort.setzen(0,0,0);
                                e0.setzen(1,0,0);
                                e1.setzen(0,0,1);
                                addierensektion(L"Konstruktionsparameter"); 
                                sektion(L"Konstruktionsparameter")->offen(true);
                                einhaengendialog(this);
                                verstecken();
};
template<class OB> _dialogboden<OB>::~_dialogboden(){
};
template<class OB> void _dialogboden<OB>::aktivieren(){
                                OB*ob=0;
                                if(hauptfenster->corundwelt){
                                 bool anwahlnutzen=false;
                                 if(hauptfenster->anwahlnetzliste.erstes()){
                                  if(hauptfenster->abfrage("Konstruktion von Böden","Sie haben ein Netz angewählt. Soll dieses Netz dupliziert werden, um daraus einen Boden zu konstruieren?")){
                                   anwahlnutzen=true;
                                  };
                                 };
                                 if(anwahlnutzen){                                 
                                  //leeren boden erzeugen und Zuweisung durchführen
                                  ob=new OB(hauptfenster->corundwelt,ort,e0,e1);
                                  _netz*n=hauptfenster->anwahlnetzliste.erstes()->objekt()->duplizieren();
                                  ob->_netz::subtraktiv(n->subtraktiv());
                                  ob->_netz::keinbsp(n->keinbsp());
                                  ob->_netz::schattenvolumen(n->schattenvolumen());
                                  ob->_netz::schattenvolumenlaenge(n->schattenvolumenlaenge());
                                  ob->_netz::brechzahl(n->brechzahl());
                                  ob->_netz::dispersionsskalierung(n->dispersionsskalierung());
                                  ob->_netz::vereinigen(n);
                                  ob->_netz::einhaengen(hauptfenster->corundwelt->welt);
                                  _corundboden*osb=ob;//dynamic_cast<_corundstein*>(pnetz);
                                  osb->nachbereitenkonstruktion();
                                  hauptfenster->zeichnen();
                                 }else{
                                  zeigen();
                                 };
                                }else{
                                 hauptfenster->information("Hinweis","Sie müssen erst eine Welt erzeugen, bevor Sie einen Boden konstruieren können.");
                                };




                             /*   if(hauptfenster->corundwelt){
                                 zeigen();
                                }else{
                                 hauptfenster->information("Hinweis","Sie müssen erst eine Welt erzeugen, bevor Sie einen boden konstruieren können.");
                                };*/
};
template<class OB> void _dialogboden<OB>::knopfok(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfok(ep);
                                erzeugen();
};
template<class OB> void _dialogboden<OB>::knopfuebernehmen(_guiereignisdaten *ep){
                                _dynamischerdialog::knopfuebernehmen(ep);
                                erzeugen();
}; 
template<class OB> OB* _dialogboden<OB>::erzeugen(){
                                if(hauptfenster->corundwelt){
                                 OB*cb=new OB(hauptfenster->corundwelt,ort,e0,e1);
                                 //co->nachbereitenkonstruktion();
                                _geometrienetz*gb;
                                gb=new _geometrienetz(hauptfenster->corundwelt->welt,ort,e0,e1,hauptfenster->corundwelt->textur[0]);
                                gb->texturkoordinatenlaenge(e0.laenge(),e1.laenge());
                                _netz*temp=gb->erzeugen();
                                cb->_netz::vereinigen(temp);
                                cb->_netz::einhaengen(hauptfenster->corundwelt->welt);
                                cb->_netz::subtraktiv(false);
                                cb->_netz::lightmapschattierung(true);
                                cb->_netz::keinbsp(true);
                                cb->_netz::schattenvolumen(false);
                                cb->_netz::schattenvolumenlaenge(10);
                                cb->_netz::nurkollisionskopplung(false);
                                delete gb;  
                                 
                                 hauptfenster->zeichnen();
                                 return(cb);
                                };
                                return(0);
};
template<class OB> void _dialogboden<OB>::einhaengendialog(_dynamischerdialog*d){
                                d->editierbar(this);
                                einhaengen(L"Konstruktionsparameter",L"Ort",ort);
                                new _editionskopplungort(d,L"Konstruktionsparameter",L"Ort");
                                einhaengen(L"Konstruktionsparameter",L"Richtung 0",e0);
                                einhaengen(L"Konstruktionsparameter",L"Richtung 1",e1);

                                
};
template<class OB> void _dialogboden<OB>::auslesendialog(_dynamischerdialog*d){
                               // d->editierbar(this);
                                auslesen(L"Konstruktionsparameter",L"Ort",ort);
                                auslesen(L"Konstruktionsparameter",L"Richtung 0",e0);
                                auslesen(L"Konstruktionsparameter",L"Richtung 1",e1);

};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G N E T Z W A H L
//******************************************************************************************************************************************************************************************************
class _dialognetzwahl:public _guidialog{
        public:
                _dialognetzwahl(_hauptfenster*hf,_guifenster*parent);
                virtual ~_dialognetzwahl();
                void corundstein(_corundstein*);
                void corundobjekt(_corundobjekt*);
                void corundboden(_corundboden*);

                void corundfigur(_corundfigur*);
                void index(const int);
                int index()const;
        protected:                
                void beiok(_guiereignisdaten *); 
                void beiabbruch(_guiereignisdaten *); 
        private:
                _hauptfenster*hauptfenster;     
                _corundstein*pcorundstein;     
                _corundobjekt*pcorundobjekt;     
                _corundboden*pcorundboden;     
             
                _corundfigur*pcorundfigur;
                int pindex;      
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G S C H A L T K O P P L U N G W A H L 
//******************************************************************************************************************************************************************************************************
template<class T>class _dialogschaltkopplungwahl:public _guidialog{
        public:
                _dialogschaltkopplungwahl(_hauptfenster*hf,_guifenster*parent);
                virtual ~_dialogschaltkopplungwahl();
                void corundschalter(_corundschalter<T>*);
                void index(const int);
                int index()const;
        protected:                
                void beiok(_guiereignisdaten *); 
                void beiabbruch(_guiereignisdaten *); 
        private:
                _hauptfenster*hauptfenster;     
                _corundschalter<T>*pcorundschalter;
                int pindex;      
};
template<class T>_dialogschaltkopplungwahl<T>::_dialogschaltkopplungwahl(_hauptfenster*hf,_guifenster*parent):_guidialog(L"Schaltkopplungwahl treffen",parent){
                                hauptfenster=hf;
                                pcorundschalter=0;
                                pindex=0;
                                erzeugen(WS_CAPTION| WS_BORDER);
                                zentrieren(120, 40, false);
                                *this += new _guiereignisClose<_dialogschaltkopplungwahl>(this, &_dialogschaltkopplungwahl::beiok);                                
                                _guiknopfdruck*button;
                                // OK 
                                button = new _guiknopfdruck(L"Schaltkopplung wählen", this, new _guiereignisCommand<_dialogschaltkopplungwahl>(this, &_dialogschaltkopplungwahl::beiok)); 
                                *button += new _guiort<>(0, 0,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 
                                // Abbruch
                                button = new _guiknopfdruck(L"Abbruch", this, new _guiereignisCommand<_dialogschaltkopplungwahl>(this, &_dialogschaltkopplungwahl::beiabbruch)); 
                                *button += new _guiort<>(0, 0.5,false); 
                                *button += new _guigroesse<>(1, 0.5,false); 
                                button->zeigen(); 

};                                
template<class T>_dialogschaltkopplungwahl<T>::~_dialogschaltkopplungwahl(){
};
template<class T>void _dialogschaltkopplungwahl<T>::index(const int i){
                                pindex=i;
};
template<class T>int _dialogschaltkopplungwahl<T>::index()const{
                                return(pindex);
};
template<class T>void _dialogschaltkopplungwahl<T>::corundschalter(_corundschalter<T>*os){
                                pcorundschalter=os;
};
template<class T>void _dialogschaltkopplungwahl<T>::beiok(_guiereignisdaten *){
                                if(hauptfenster->anwahlnetzliste.erstes()){
                                 _corundschaltkopplung*c=dynamic_cast<_corundschaltkopplung*>(hauptfenster->anwahlnetzliste.erstes()->objekt());
                                 if(c){
                                  if(pcorundschalter) pcorundschalter->schaltkopplungwahl(c,pindex);
                                 }else hauptfenster->information("Hinweis","Das angewählte Netz enthält keine Schaltkopplung als Subtyp (Crosscast erfolglos).");
                                 verstecken();
                                }else if(hauptfenster->anwahllicht) {
                                 _corundschaltkopplung*cl=dynamic_cast<_corundschaltkopplung*>(hauptfenster->anwahllicht);
                                 if(cl){
                                  if(pcorundschalter) pcorundschalter->schaltkopplungwahl(cl,pindex);
                                 }else hauptfenster->information("Hinweis","Das angewählte Netz enthält keine Schaltkopplung als Subtyp (Crosscast erfolglos).");
                                 verstecken();
                                }else hauptfenster->information("Hinweis","Wählen Sie ein Netz oder Licht (ein Schaltbares Objekt) aus und drücken dann die Schaltfläche.");
};                    

template<class T>void _dialogschaltkopplungwahl<T>::beiabbruch(_guiereignisdaten *){
                                verstecken();
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G K N O T E N W A H L 
//******************************************************************************************************************************************************************************************************
class _dialogknotenwahl:public _guidialog{
        public:
                _dialogknotenwahl(_hauptfenster*hf,_guifenster*parent);
                virtual ~_dialogknotenwahl();
                void corundstein(_corundstein*);
                void corundobjekt(_corundobjekt*);
                void corundboden(_corundboden*);
                void corundfigur(_corundfigur*);
                void index(const int);
                int index()const;
        protected:                
                void beiok(_guiereignisdaten *); 
                void beiabbruch(_guiereignisdaten *); 
        private:
                _hauptfenster*hauptfenster;     
                _corundstein*pcorundstein;     
                _corundobjekt*pcorundobjekt;     
                _corundboden*pcorundboden;     
                _corundfigur*pcorundfigur;     
                int pindex;      
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F I G U R W A H L
//******************************************************************************************************************************************************************************************************
class _dialogfigurwahl:public _guidialog{
        public:
                _dialogfigurwahl(_hauptfenster*hf,_guifenster*parent);
                virtual ~_dialogfigurwahl();
                void corundstein(_corundstein*);
                void corundobjekt(_corundobjekt*);
                void corundboden(_corundboden*);
                void corundfigur(_corundfigur*);
                void index(const int);
                int index()const;
        protected:                
                void beiok(_guiereignisdaten *); 
                void beiabbruch(_guiereignisdaten *); 
        private:
                _hauptfenster*hauptfenster;     
                _corundstein*pcorundstein;     
                _corundobjekt*pcorundobjekt;     
                _corundboden*pcorundboden;     
                _corundfigur*pcorundfigur;
                int pindex;      
};
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G K N O T E N
//******************************************************************************************************************************************************************************************************
class _dialogknoten:public _dynamischerdialog,_editierbar{
        public:
                _dialogknoten(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogknoten();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> plocus;
                unsigned int index;
                _vektor3<_tg> vektorankunft;
                _vektor3<_tg> vektorabfahrt;
                unsigned int wartezeit;
                
}; 
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G F R A K T A L 
//******************************************************************************************************************************************************************************************************
class _dialogfraktal:public _dynamischerdialog,_editierbar{
        public:
                _dialogfraktal(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogfraktal();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                virtual void zeigen();
                virtual void verstecken();
                void beiknopfruecksetzen(_guiereignisdaten*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> plocus;
                _vektor3<_tg> pe0;
                _vektor3<_tg> pe1;
                _vektor3<_tg> pe2;
                _vektor3<_tg> pschiebrichtung;
                _fraktal<_tg> fr;
                _netz*original;

};  
//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G B I E G E N
//******************************************************************************************************************************************************************************************************
class _dialogbiegen:public _dynamischerdialog,_editierbar{
        public:
                _dialogbiegen(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogbiegen();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> port;
                _vektor3<_tg> protaxis;
                _vektor3<_tg> pwaxis;
                _tg pwinkel;
};          

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G R O T I E R E N
//******************************************************************************************************************************************************************************************************
class _dialogrotieren:public _dynamischerdialog,_editierbar{
        public:
                _dialogrotieren(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogrotieren();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> port;
                _vektor3<_tg> protaxis;
                _tg pwinkel;
};          

//******************************************************************************************************************************************************************************************************
//                                                             D I A L O G V E R D R E H E N 
//******************************************************************************************************************************************************************************************************
class _dialogverdrehen:public _dynamischerdialog,_editierbar{
        public:
                _dialogverdrehen(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
                virtual ~_dialogverdrehen();
                void erzeugen();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
        private:
                _hauptfenster*hauptfenster;  
                _vektor3<_tg> port;
                _vektor3<_tg> protaxis;
                _tg pwinkel;
        
};  
/*
//******************************************************************************************************************************************************************************************************
//                                                             D Y N A M I S C H E R D I A L O G M U L T I 
//******************************************************************************************************************************************************************************************************
class _dynamischerdialogmulti:public _dynamischerdialog{
		public:
				_dialogmulti(_hauptfenster*hf,const T_String<>&pn,_guifenster*parent);
				virtual ~_dialogmulti();
                virtual void knopfok(_guiereignisdaten *);  // Muss in der Anwendung überladen werden können... 
                virtual void knopfuebernehmen(_guiereignisdaten *); 				
		private:
				_liste<_editierbar> pliste;				
};
*/
#endif