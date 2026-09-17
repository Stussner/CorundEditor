#ifndef _oxyydansicht_included
#define _oxyydansicht_included

class _texturansicht;
class _schnitt;
class _ansicht;

#include "../hpp/_corundeditor.hpp"
#include "../../oxyd/hpp/_corundfigur.hpp"
#include <_struktur.hpp>

//******************************************************************************************************************************************************************************************************
//                                                              T E X T U R A N S I C H T
//******************************************************************************************************************************************************************************************************
class _texturansicht:public _guifensterkarteiseite{
        public:
                _texturansicht(_hauptfenster*,_guifensterkartei*tw);
                virtual ~_texturansicht();
                void aktualisieren();
                _textur<_tb>*anwahl();
                void bindentextur(_grafik*,_textur<_tb>*,_bild<_tb>*&,_bild<_tb>*&,_bild<_tb>*&);
                void beigroesse(_guiereignisdaten *);
                void beimauslinksein(_guiereignisdaten *);
                void zeichnen(_guiereignisdaten *);
                
        private:
                _hauptfenster*hauptfenster;
                 _grafik*grafik;
                _guikontext*pdc;  // muss kein zeiger sein
                _guiscrollbarvertikal*scrollbar;
                _textur<_tb>*panwahl;

};
//******************************************************************************************************************************************************************************************************
//                                                              S C H N I T T 
//******************************************************************************************************************************************************************************************************
class _schnitt{
        public:
                _schnitt(_listesortiert<_schnitt,_tg>*,_polygon*,_tg);
                _schnitt(_listesortiert<_schnitt,_tg>*,_licht<_tg,_to>*,_tg);
                _schnitt(_listesortiert<_schnitt,_tg>*,_corundknoten*,_tg);
                _schnitt(_listesortiert<_schnitt,_tg>*,_gravitation<_tg>*,_tg);
                _schnitt(_listesortiert<_schnitt,_tg>*,_feldelektrostatisch<_tg>*,_tg);
                _schnitt(_listesortiert<_schnitt,_tg>*,_feldmagnetostatisch<_tg>*,_tg);
                _schnitt(_listesortiert<_schnitt,_tg>*,_partikelquelle*,_tg);
                _schnitt(_listesortiert<_schnitt,_tg>*,_corundkugel*,_tg);
                virtual ~_schnitt();
                void init();
        public:
                _polygon*polygon;
                _licht<_tg,_to>*licht;
                _corundknoten*knoten;
                _partikelquelle*partikelquelle;
                _gravitation<_tg>*gravitation;
                _feldelektrostatisch<_tg>*feldelektrostatisch;
                _feldmagnetostatisch<_tg>*feldmagnetostatisch;
                _corundkugel*kugel;                
};
//******************************************************************************************************************************************************************************************************
//                                                              A N S I C H T
//******************************************************************************************************************************************************************************************************
class _ansicht:public _guifensterkind{
        public:
                _ansicht(_hauptfenster*,_guifenster*dummy,const _zeichenkette<char>&);
                ~_ansicht();
                
				bool innerhalbtiefe(_polygon*p,_tg c0,_tg c1);
				void sichttiefe(_tg&c0,_tg&c1);      
                void holennetze(_netz*&n,_liste<_netz>*lop);
                
                void beigroesse(_guiereignisdaten *);
                void beimauslinksdoppelklick(_guiereignisdaten*);
                void beimausrechtsdoppelklick(_guiereignisdaten*);
                
                void beimauslinksein(_guiereignisdaten *);
                void beimauslinksaus(_guiereignisdaten *);
                void beimausrechtsein(_guiereignisdaten *);
                void beimausrechtsaus(_guiereignisdaten *);
                void beimausrad(_guiereignisdaten *);
                void beimausbewegung(_guiereignisdaten *);
                
                void zeichnengrid(_tg teilung);
                void zeichnen(_guiereignisdaten *);
                void zeichnensteinschablone(_netz*n);
                void pruefenkollisionkopplungen(const _vektor2<_tg>&m,_editionskopplung*&e);
                void pruefenkollision(const _vektor2<_tg>&m); 
                void anwaehlen(_polygon*pit,_vektor3<_tg>);
				void loeschenanwahl();
                void loeschenschnittliste();
                
                void beibearbeitenvertex(_guiereignisdaten*);
                void beibearbeitenpolygon(_guiereignisdaten*);
                void beibearbeitenpolygontexturgeometrie(_guiereignisdaten*);
                void beiloeschenpolygon(_guiereignisdaten*);
                void beibearbeitennetz(_guiereignisdaten*);
                void beikopierennetz(_guiereignisdaten*);
                void beiinvertieren(_guiereignisdaten*);
                void beiverschiebenraster(_guiereignisdaten*);
                void beitauschenxy(_guiereignisdaten*);
                void beitauschenxz(_guiereignisdaten*);
                void beitauschenyz(_guiereignisdaten*);
                void beispiegelnx(_guiereignisdaten*);
                void beispiegelny(_guiereignisdaten*);
                void beispiegelnz(_guiereignisdaten*);
                void beiintersektionnetz(_guiereignisdaten*);
                void beideintersektionnetz(_guiereignisdaten*);
                void beivereinigungnetz(_guiereignisdaten*);
                void beivereinigungnetzwelt(_guiereignisdaten*);
                void beivereinigungnetzohneschnitt(_guiereignisdaten*);
                void beiteilungnetz(_guiereignisdaten*);
                void beinetztexturneuskalieren(_guiereignisdaten*);
                void beinetzkomplanarenichtzeichnen(_guiereignisdaten*);
                void beinetzkomplanarenichtkollidieren(_guiereignisdaten*);
                void beinetzkomplanarekeinschattenwurflightmap(_guiereignisdaten*);
                void beifraktal(_guiereignisdaten*);
                void beibiegen(_guiereignisdaten*);
                void beirotieren(_guiereignisdaten*);
                void beiverdrehen(_guiereignisdaten*);
                void beiskalierenmul2(_guiereignisdaten*);
                void beiskalierendiv2(_guiereignisdaten*);
                void beiloeschennetz(_guiereignisdaten*);
                void beispeichernnetz(_guiereignisdaten*);
                
                void beibearbeitenlicht(_guiereignisdaten*);
                void beikopierenlicht(_guiereignisdaten*);
                void beiloeschenlicht(_guiereignisdaten*);

                void beibearbeitenknoten(_guiereignisdaten*);
                void beiloeschenknoten(_guiereignisdaten*);

                void beibearbeitengravitation(_guiereignisdaten*);
                void beiloeschengravitation(_guiereignisdaten*);
                
                void beibearbeitenfeldelektrostatisch(_guiereignisdaten*);
                void beiloeschenfeldelektrostatisch(_guiereignisdaten*);
                
                void beibearbeitenfeldmagnetostatisch(_guiereignisdaten*);
                void beiloeschenfeldmagnetostatisch(_guiereignisdaten*);
                
                void beibearbeitenpartikelquelle(_guiereignisdaten*);
                void beikopierenpartikelquelle(_guiereignisdaten*);
                void beiloeschenpartikelquelle(_guiereignisdaten*);
                
                void beibearbeitenkugel(_guiereignisdaten*);
                void beiloeschenkugel(_guiereignisdaten*);
        public:      
                _hauptfenster*hauptfenster;          
                _guimenue*menuvertex;
                _guimenue*menupolygon;
                _guimenue*menunetz;                
                _guimenue*menulicht;         
                _guimenue*menuknoten;         
                _guimenue*menupartikelquelle;       
                _guimenue*menugravitation;                
                _guimenue*menufeldelektrostatisch;                
                _guimenue*menufeldmagnetostatisch;                
                _guimenue*menukugel;
                _zeichenkette<char> name;
                _guikontext*pdc;  // muss kein zeiger sein
                
                 _grafik*grafik;
                
                _kamera<_tg>*kamera;
                _vektor4<_to> farbe;
                int modus;//0==normale verschiebung, 1==kopplungsverschiebung
                _editionskopplung*editionskopplung;
                
                bool istxz;
                bool istxy;
                bool istyz;
                _ansicht*sichtkopplung0;
                _ansicht*sichtkopplung1;
                
        private:                
                bool links;
                bool rechts;
                _vektor2<_tg> altepos;
                _vektor3<_tg> bewegungsakku;
                _vektor2<_tg> alteschnittpos;
                _listesortiert<_schnitt,_tg> ls;
                _listenknotensortiert<_schnitt,_tg> *lnsit;
                _vektor3<_tg> dir;
                _vektor3<_tg> start;                
};
#endif