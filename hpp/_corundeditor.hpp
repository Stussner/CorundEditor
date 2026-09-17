#ifndef _corundeditor_hpp_included
#define _corundeditor_hpp_included

class _corundwelt;
class I_Sound;
class _tonverwaltung;
class _corundkugel;
class _corundstein;
class _corunddialog;
class _corundsteincorund;
template<class T>class _dialoggeometrie;
class _dialogtexturgeometrie;
class _dialogkugel;
template<class OS>class _dialogstein;
class _dialognetzwahl;
class _dialoggravitation;
class _dialogfeldelektrostatisch;
class _dialogfeldmagnetostatisch;
class _dialogpartikelquellesprite;
class _dialoglicht;
class _hauptfenster;
class _haupttoolbar;
class _ansicht;

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <_global.hpp>
#include <_struktur.hpp>
#include <_funktion.hpp>
#include <_text.hpp>
#include <_textbuffer.hpp>
#include <_datei.hpp>
#include <_bild.hpp>

#ifdef CORUND_MIT_OPENGL
 #include <_grafikopengl.hpp>
#else
 #include <_grafikdirectx.hpp>
#endif
#include <_akustikopenal.hpp>
#include <_welt.hpp>
#include <_weltpolygon.hpp>
#include <_weltoptik.hpp>   
#include <_weltfigur.hpp>
#include <_weltmechanik.hpp>
#include <_weltkollision.hpp>
#include <_editionwin.hpp>
#include <_welt3ds.hpp>
//#include "../hpp/_corundstein.hpp"
#include "../../oxyd/hpp/_corundobjekt.hpp"
#include "../../oxyd/hpp/_corundboden.hpp"
#include "../../oxyd/hpp/_corund.hpp"
#include "../hpp/_corunddialog.hpp"
#include "../hpp/_corundansicht.hpp"
//#include <BCGUI/Dialogs/modaldialog.hpp>
//#include <BCGUI/Dialogs/filedialog.hpp>
//#include <BCGUI/Windows/splashwindow.hpp>
//#define WIN32_LEAN_AND_MEAN



//******************************************************************************************************************************************************************************************************
//                                                              H A U P T F E N S T E R 
//******************************************************************************************************************************************************************************************************


class _hauptfenster : 
 public _guifensterhaupt,
 public _editierbar,
 public _listebasis<_kamera<_tg> >,
 public _listebasis<_geometrie>,
 public _listebasis<_dynamischerdialog>,
 public _besitzeraktualisierung{
        public:
                using _listebasis<_kamera<_tg> >::anfang;
                using _listebasis<_kamera<_tg> >::naechstes;
                using _listebasis<_kamera<_tg> >::vorheriges;
                using _listebasis<_geometrie>::anfang;
                using _listebasis<_geometrie>::naechstes;
                using _listebasis<_geometrie>::vorheriges;
                using _listebasis<_dynamischerdialog>::anfang;
                using _listebasis<_dynamischerdialog>::naechstes;
                using _listebasis<_dynamischerdialog>::vorheriges;
        public:
                _hauptfenster(T_String<> const &name);
                virtual ~_hauptfenster(); 
                void ladensamples();
                void ladentexturen();
                void ladentextur(unsigned int i,_zeichenkette<char> s,bool);
                
                void aktualisieren();
                void zeichnen();
                void loeschenanwahl();
                
                void beinichtdefiniert(_guiereignisdaten*);

                void beischliessen(_guiereignisdaten*);
                void beizerstoeren(_guiereignisdaten*);  
                void beikonversion(_guiereignisdaten*);
                void beieigenschaften(_guiereignisdaten*); 
                
                void beiweltneu(_guiereignisdaten*);
                void beiweltladen(_guiereignisdaten*);
                void beiweltladenhart(_guiereignisdaten*);
                void beiweltimportieren(_guiereignisdaten*);
                void beiweltspeichern(_guiereignisdaten*);
                void beiweltschliessen(_guiereignisdaten*);
                void beiweltzonenvorerstellen(_guiereignisdaten*);
                void beiweltzonenerstellen(_guiereignisdaten*);
                void beiweltzonenloeschen(_guiereignisdaten*);
                void beiweltzonenbestrahlen(_guiereignisdaten*);
                void beiwelttestenohnebestrahlung(_guiereignisdaten*);
                void beiwelttesten(_guiereignisdaten*);
                void beiwelttestenverbund(_guiereignisdaten*);
                void beiwelttestenspinnmania(_guiereignisdaten*);
                void beiweltkomplanarenichtzeichnen(_guiereignisdaten*);
                void beiweltkomplanarenichtkollidieren(_guiereignisdaten*);
                void beiweltkomplanarekeinschattenwurflightmap(_guiereignisdaten*);
                void netzkomplanarenichtzeichnen(_netz*);
                void netzkomplanarenichtkollidieren(_netz*);
                void netzkomplanarekeinschattenwurflightmap(_netz*);
                void beiwelteigenschaften(_guiereignisdaten*);
                
                void beiumgebungschwarz(_guiereignisdaten*);
                void beiumgebungbergpanoramaheiter(_guiereignisdaten*);
                
                void beinetznetz(_guiereignisdaten*); 
                void beinetzscheibe(_guiereignisdaten*); 
                void beinetzquader(_guiereignisdaten*); 
                void beinetzkreuzbalken(_guiereignisdaten*); 
                void beinetzzylinder(_guiereignisdaten*); 
                void beinetzkonus(_guiereignisdaten*); 
                void beinetzkugel(_guiereignisdaten*); 
                void beinetztorus(_guiereignisdaten*); 
                void beinetzflaechehermite(_guiereignisdaten*); 

                void beilichtlicht(_guiereignisdaten*); 
                
                void beiknotenknoten(_guiereignisdaten*);

                void beifigurkugel(_guiereignisdaten*); 
                void beifigurspinne(_guiereignisdaten*); 
                void beifigurorakel(_guiereignisdaten*); 
                void beifigurhebweber(_guiereignisdaten*); 
                void beifigurspringspinne(_guiereignisdaten*); 
                void beifigurcatwiesel(_guiereignisdaten*); 
                void beifigurfliege(_guiereignisdaten*); 
                void beifigurmade(_guiereignisdaten*); 
                
                
                template<class OS> OS* erzeugencorundstein(OS*schablone);
                void beisteinnormal(_guiereignisdaten*);
                void beisteincorund(_guiereignisdaten*);
                void beisteingummiband(_guiereignisdaten*);
                void beisteinschere(_guiereignisdaten*);
                void beisteinschieb(_guiereignisdaten*);
                void beisteinboulder(_guiereignisdaten*);
                void beisteinrotation(_guiereignisdaten*);
                void beisteinimpuls(_guiereignisdaten*);
                void beisteinelektrisch(_guiereignisdaten*);
                void beisteinerdung(_guiereignisdaten*);
                void beisteinbeschleunigung(_guiereignisdaten*);
                void beisteintotenkopf(_guiereignisdaten*);
                void beisteintor(_guiereignisdaten*);
                void beisteinschalter(_guiereignisdaten*);
                void beisteinkugelgen(_guiereignisdaten*);
                void beisteindach(_guiereignisdaten*);
                void beisteinflak(_guiereignisdaten*);
                void beisteinausgang(_guiereignisdaten*);
                void beisteinsenker(_guiereignisdaten*);
                void beisteinlaser(_guiereignisdaten*);
                void beisteinspiegel(_guiereignisdaten*);
                void beisteinschloss(_guiereignisdaten*);
                void beisteinereignis(_guiereignisdaten*);
                void beisteingerissen(_guiereignisdaten*);
                void beisteinspuck(_guiereignisdaten*);
                void beisteintauscher(_guiereignisdaten*);
                void beisteinmagnetisch(_guiereignisdaten*);
                void beisteindieb(_guiereignisdaten*);
                void beisteinfliegengen(_guiereignisdaten*);
                void beisteinspinnengen(_guiereignisdaten*);
                void beisteinshogun(_guiereignisdaten*);
                void beisteinpuzzle(_guiereignisdaten*);
                void beisteingas(_guiereignisdaten*);
                void beisteinkombinationsschloss(_guiereignisdaten*);
                void beisteindrehkreuz(_guiereignisdaten*);
                void beisteineinbahn(_guiereignisdaten*);
                
                void beiobjektersatz(_guiereignisdaten*);
                void beiobjektschluessela(_guiereignisdaten*);
                void beiobjektbombe(_guiereignisdaten*);
                void beiobjektdynamit(_guiereignisdaten*);
                void beiobjektmine(_guiereignisdaten*);
                void beiobjektsteinpille(_guiereignisdaten*);
                void beiobjektalkohol(_guiereignisdaten*);
                void beiobjektbungeeseil(_guiereignisdaten*);
                void beiobjektschere(_guiereignisdaten*);
                void beiobjektzettel(_guiereignisdaten*);
                void beiobjektfallschirm(_guiereignisdaten*);
                void beiobjektzauberstab(_guiereignisdaten*);
                void beiobjekttriebwerk(_guiereignisdaten*);
                void beiobjektgesundheit(_guiereignisdaten*);
                void beiobjektreisszwecke(_guiereignisdaten*);
                void beiobjekthammer(_guiereignisdaten*);
                void beiobjektgasbrenner(_guiereignisdaten*);
                void beiobjektschutzschild(_guiereignisdaten*);
                void beiobjektschneidbrenner(_guiereignisdaten*);
                void beiobjektschwarzesloch(_guiereignisdaten*);
                void beiobjektmagnet(_guiereignisdaten*);
                void beiobjektpresslufthammer(_guiereignisdaten*);
                void beiobjektteleporter(_guiereignisdaten*);
                void beiobjektgleitmittel(_guiereignisdaten*);
                void beiobjektgeld(_guiereignisdaten*);
                void beiobjektsprungfeder(_guiereignisdaten*);
                void beiobjektskalierer(_guiereignisdaten*);
                void beiobjektpflanze(_guiereignisdaten*);
                void beiobjektobst(_guiereignisdaten*);
                void beiobjektdematerialisierung(_guiereignisdaten*);
                void beiobjektdevisualisierung(_guiereignisdaten*);
                void beiobjektinsektenspray(_guiereignisdaten*);
                void beiobjektfeuerloescher(_guiereignisdaten*);
                void beiobjektsummer(_guiereignisdaten*);
                void beiobjektblinker(_guiereignisdaten*);
                void beiobjektbatterie(_guiereignisdaten*);
                void beiobjektpinsel(_guiereignisdaten*);
                void beiobjektbesen(_guiereignisdaten*);
                void beiobjektlampe(_guiereignisdaten*);
                void beiobjektkerze(_guiereignisdaten*);
                void beiobjektgewicht(_guiereignisdaten*);
                void beiobjektgasmaske(_guiereignisdaten*);
                void beiobjektschutzhelm(_guiereignisdaten*);
                void beiobjektspritze(_guiereignisdaten*);  

                void beibodennormal(_guiereignisdaten*);
                void beibodenschalter(_guiereignisdaten*);
                void beibodeninvers(_guiereignisdaten*);
                void beibodenweltraum(_guiereignisdaten*);
                void beibodeneis(_guiereignisdaten*);
                void beibodensand(_guiereignisdaten*);
                void beibodenschnee(_guiereignisdaten*);
                void beibodenwiese(_guiereignisdaten*);
                void beibodenwasser(_guiereignisdaten*);
                void beibodensumpf(_guiereignisdaten*);
                void beibodenlava(_guiereignisdaten*);
                void beibodenbeschleunigung(_guiereignisdaten*);
                void beibodengradienz(_guiereignisdaten*);
                void beibodentransport(_guiereignisdaten*);
                void beibodentotenkopf(_guiereignisdaten*);                 
                
                void beigravitation(_guiereignisdaten*); 
                void beiefeld(_guiereignisdaten*); 
                void beibfeld(_guiereignisdaten*); 
                
                void beipartikelquelleintern(_guiereignisdaten*);
                void beipartikelquellesprite(_guiereignisdaten*);

                void beigroesse(_guiereignisdaten*);
                void beigroessedummyoben(_guiereignisdaten*);
                void beigroessedummyunten(_guiereignisdaten*);
                
                void testenwelt(bool lightmaps,bool verbund);
                void testenwelteinzel(bool lightmaps);
                void testenweltuebersetzen(_liste<_netz>*&rohnetze);
                void testenweltbestrahlen(_partition::_zone*zit,bool lightmaps);
                void testenweltloeschenlightmap();
                void testenweltanlegenlightmap(bool lightmaps);
                void testenweltunuebersetzen(_liste<_netz>*rohnetze);
                
                
                void beiknopferzeugenbaum(_guiereignisdaten*);
                virtual void einhaengendialog(_dynamischerdialog*);
                virtual void auslesendialog(_dynamischerdialog*);
                
                unsigned int abfrage(const _zeichenkette<char>&,const _zeichenkette<char>&);
                unsigned int information(const _zeichenkette<char>&,const _zeichenkette<char>&);
                
        public:
                _corundwelt*corundwelt;
                _akustik*akustik;//I_Sound*sound;
                _texturverwaltung<_tb>*texturverwaltung;
                _tonverwaltung*tonverwaltung;
                bool testmodus;
                _tastatur*tastatur;
                _liste<_editionskopplung> editionskopplungen;
                //------------- fenster elemente ---------------
                _ansicht*ansicht[4];
                _guifenster*dummyganz;
                _guifenster*dummyoben;
                _guifenster*dummyunten;
                _guiteilerhorizontal*splitterhorizontal;
                _guiteilervertikal*splittervertikal[2];
                _guifensterkartei*tabwindow;
                _guistatusleiste*statusbar;
                _haupttoolbar*toolbar;
                _texturansicht*texturansicht;
                //------------ menu ---------------------
                _guimenueleiste*menubar;                 
                _guimenue*menueditor;
                _guimenue*menuwelt;
                _guimenue*menuumgebung;
                _guimenue*menunetz;
                _guimenue*menulicht;
                _guimenue*menuknoten;
                _guimenue*menustein;
                _guimenue*menuobjekt;
                _guimenue*menuboden;
                _guimenue*menufigur;
                _guimenue*menugravitation;
                _guimenue*menupartikelquelle;
                _guimenue*menusound;
                _guimenue*menufeldquelle;
                _guimenue*menuaerodynamik;
                _guimenue*menufluiddynamik;
                //------------- dialoge -------------------
                _corunddialog*dyndialog;
                _dialoghart*dhart;
                _dialogtexturgeometrie*dtexturgeometrie;
                _dialoglicht*dlicht;
                _dialogknoten*dknoten;
                _dialogfraktal*dfraktal;
                _dialogbiegen*dbiegen;
                _dialogrotieren*drotieren;
                _dialogverdrehen*dverdrehen;
                _dialogumgebung*dumgebung;
                
                
                _dialogkugel*dkugel;
                _dialogspinne*dspinne;
                _dialogfigur<_corundorakel>*dorakel;
                _dialogfigur<_corundhebweber>*dhebweber;
                _dialogfigur<_corundspringspinne>*dspringspinne;
                _dialogfigur<_corundcatwiesel>*dcatwiesel;
                _dialogfigur<_corundfliege>*dfliege;
                _dialogfigur<_corundmade>*dmade;
                
                _dialogstein<_corundstein>*dsteinnormal;
                _dialogstein<_corundsteincorund>*dsteincorund;
                _dialogstein<_corundsteingummiband>*dsteingummiband;
                _dialogstein<_corundsteinschere>*dsteinschere;
                _dialogstein<_corundsteinschieb>*dsteinschieb;
                _dialogstein<_corundsteinboulder>*dsteinboulder;
                _dialogstein<_corundsteinrotation>*dsteinrotation;
                _dialogstein<_corundsteinimpuls>*dsteinimpuls;
                _dialogstein<_corundsteinelektrisch>*dsteinelektrisch;
                _dialogstein<_corundsteinerdung>*dsteinerdung;
                _dialogstein<_corundsteinbeschleunigung>*dsteinbeschleunigung;
                _dialogstein<_corundsteintotenkopf>*dsteintotenkopf;
                _dialogstein<_corundsteintor>*dsteintor;
                _dialogstein<_corundsteinschalter>*dsteinschalter;
                _dialogstein<_corundsteinkugelgen>*dsteinkugelgen;
                _dialogstein<_corundsteindach>*dsteindach;
                _dialogstein<_corundsteinflak>*dsteinflak;
                _dialogstein<_corundsteinausgang>*dsteinausgang;
                _dialogstein<_corundsteinsenker>*dsteinsenker;
                _dialogstein<_corundsteinlaser>*dsteinlaser;
                _dialogstein<_corundsteinspiegel>*dsteinspiegel;
                _dialogstein<_corundsteinschloss>*dsteinschloss;
                _dialogstein<_corundsteinereignis>*dsteinereignis;
                _dialogstein<_corundsteingerissen>*dsteingerissen;
                _dialogstein<_corundsteinspuck>*dsteinspuck;
                _dialogstein<_corundsteintauscher>*dsteintauscher;
                _dialogstein<_corundsteinmagnetisch>*dsteinmagnetisch;
                _dialogstein<_corundsteindieb>*dsteindieb;
                _dialogstein<_corundsteinfliegengen>*dsteinfliegengen;
                _dialogstein<_corundsteinspinnengen>*dsteinspinnengen;
                _dialogstein<_corundsteinshogun>*dsteinshogun;
                _dialogstein<_corundsteinpuzzle>*dsteinpuzzle;
                _dialogstein<_corundsteingas>*dsteingas;
                _dialogstein<_corundsteinkombinationsschloss>*dsteinkombinationsschloss;
                _dialogstein<_corundsteindrehkreuz>*dsteindrehkreuz;                
                _dialogstein<_corundsteineinbahn>*dsteineinbahn;                
                
                
                _dialogobjekt<_corundobjektersatz>*dobjektersatz;
                _dialogobjekt<_corundobjektschluessela>*dobjektschluessela;
                _dialogobjekt<_corundobjektbombe>*dobjektbombe;                
                _dialogobjekt<_corundobjektdynamit>*dobjektdynamit;                
                _dialogobjekt<_corundobjektmine>*dobjektmine;
                _dialogobjekt<_corundobjektsteinpille>*dobjektsteinpille;
                _dialogobjekt<_corundobjektalkohol>*dobjektalkohol;
                _dialogobjekt<_corundobjektbungeeseil>*dobjektbungeeseil;
                _dialogobjekt<_corundobjektschere>*dobjektschere;
                _dialogobjekt<_corundobjektzettel>*dobjektzettel;
                _dialogobjekt<_corundobjektfallschirm>*dobjektfallschirm;
                _dialogobjekt<_corundobjektzauberstab>*dobjektzauberstab;
                _dialogobjekt<_corundobjekttriebwerk>*dobjekttriebwerk;
                _dialogobjekt<_corundobjektgesundheit>*dobjektgesundheit;
                _dialogobjekt<_corundobjektreisszwecke>*dobjektreisszwecke;
                _dialogobjekt<_corundobjekthammer>*dobjekthammer;
                _dialogobjekt<_corundobjektgasbrenner>*dobjektgasbrenner;
                _dialogobjekt<_corundobjektschutzschild>*dobjektschutzschild;
                _dialogobjekt<_corundobjektschneidbrenner>*dobjektschneidbrenner; 
                _dialogobjekt<_corundobjektschwarzesloch>*dobjektschwarzesloch;
                _dialogobjekt<_corundobjektmagnet>*dobjektmagnet;
                _dialogobjekt<_corundobjektpresslufthammer>*dobjektpresslufthammer;
                _dialogobjekt<_corundobjektteleporter>*dobjektteleporter;
                _dialogobjekt<_corundobjektgleitmittel>*dobjektgleitmittel;
                _dialogobjekt<_corundobjektgeld>*dobjektgeld;
                _dialogobjekt<_corundobjektsprungfeder>*dobjektsprungfeder;
                _dialogobjekt<_corundobjektskalierer>*dobjektskalierer;
                _dialogobjekt<_corundobjektpflanze>*dobjektpflanze;
                _dialogobjekt<_corundobjektobst>*dobjektobst;
                _dialogobjekt<_corundobjektdematerialisierung>*dobjektdematerialisierung;
                _dialogobjekt<_corundobjektdevisualisierung>*dobjektdevisualisierung;
                _dialogobjekt<_corundobjektinsektenspray>*dobjektinsektenspray;
                _dialogobjekt<_corundobjektfeuerloescher>*dobjektfeuerloescher;
                _dialogobjekt<_corundobjektsummer>*dobjektsummer;
                _dialogobjekt<_corundobjektblinker>*dobjektblinker;
                _dialogobjekt<_corundobjektbatterie>*dobjektbatterie;
                _dialogobjekt<_corundobjektpinsel>*dobjektpinsel;
                _dialogobjekt<_corundobjektbesen>*dobjektbesen;
                _dialogobjekt<_corundobjektlampe>*dobjektlampe;
                _dialogobjekt<_corundobjektkerze>*dobjektkerze;
                _dialogobjekt<_corundobjektgewicht>*dobjektgewicht;
                _dialogobjekt<_corundobjektgasmaske>*dobjektgasmaske;
                _dialogobjekt<_corundobjektschutzhelm>*dobjektschutzhelm;
                _dialogobjekt<_corundobjektspritze>*dobjektspritze;                
                
                _dialogboden<_corundbodennormal>*dbodennormal;
                _dialogboden<_corundbodenschalter>*dbodenschalter;
                _dialogboden<_corundbodeninvers>*dbodeninvers;
                _dialogboden<_corundbodenweltraum>*dbodenweltraum;
                _dialogboden<_corundbodeneis>*dbodeneis;
                _dialogboden<_corundbodensand>*dbodensand;
                _dialogboden<_corundbodenschnee>*dbodenschnee;
                _dialogboden<_corundbodenwiese>*dbodenwiese;
                _dialogboden<_corundbodenwasser>*dbodenwasser;
                _dialogboden<_corundbodensumpf>*dbodensumpf;
                _dialogboden<_corundbodenlava>*dbodenlava;
                _dialogboden<_corundbodenbeschleunigung>*dbodenbeschleunigung;
                _dialogboden<_corundbodengradienz>*dbodengradienz;
                _dialogboden<_corundbodentransport>*dbodentransport;
                _dialogboden<_corundbodentotenkopf>*dbodentotenkopf;                
                
                _dialogschaltkopplungwahl<_corundsteincorund>*dsteincorundschaltkopplungswahl;
                _dialogschaltkopplungwahl<_corundsteinereignis>*dsteinereignisschaltkopplungswahl;
                _dialogschaltkopplungwahl<_corundsteinschloss>*dsteinschlossschaltkopplungswahl;
                _dialogschaltkopplungwahl<_corundsteinschalter>*dsteinschaltkopplungswahl;
                _dialogschaltkopplungwahl<_corundbodenschalter>*dbodenschaltkopplungswahl;
                _dialognetzwahl*dnetzwahl;
                _dialogfigurwahl*dfigurwahl;
                _dialogknotenwahl*dknotenwahl;
                _dialoggravitation*dgravitation;
                _dialogfeldelektrostatisch*dfeldelektrostatisch;
                _dialogfeldmagnetostatisch*dfeldmagnetostatisch;
                _dialogpartikelquellesprite*dpartikelquellesprite;
                
                _dialoggeometrie<_geometrienetz>*dnetz;
                _dialoggeometrie<_geometriequader>*dquader;
                _dialoggeometrie<_geometriescheibe>*dscheibe;
                _dialoggeometrie<_geometriekreuzbalken>*dkreuzbalken;
                _dialoggeometrie<_geometriezylinder>*dzylinder;
                _dialoggeometrie<_geometrietorus>*dtorus;
                _dialoggeometrie<_geometriekonus>*dkonus;
                _dialoggeometrie<_geometriekugel>*dgkugel;
                _dialoggeometrie<_geometrieflaechehermite>*dflaechehermite;
                
                _geometrienetz*gnetz;
                _geometriescheibe*gscheibe;
                _geometriequader*gquader;
                _geometriekreuzbalken*gkreuzbalken;
                _geometriezylinder*gzylinder;
                _geometriekonus*gkonus;
                _geometriekugel*gkugel;
                _geometrietorus*gtorus;
                _geometrieflaechehermite*gflaechehermite;
                //-------------- raster ------------------
                bool rasterzeichnen;
                bool rasterverwenden;
                _tg rasterbreite;
                _tg snapping;
                //------------- feld zeichnungen ----------
                bool gfeldzeichnen;
                bool efeldzeichnen;
                bool bfeldzeichnen;
                unsigned int gfeldanzahl;
                unsigned int efeldanzahl;
                unsigned int bfeldanzahl;
                //--------------- anwahl -----------------
                _tg letzteanwahl;
                
                //_vertex*anwahlvertex;
                //_polygon*anwahlpolygon;
                //_vertex*anwahlkante[2];
                //_netz*anwahlnetz;
                _licht<_tg,_to>*anwahllicht;
                _partikelquelle*anwahlpartikelquelle;
                _gravitation<_tg>*anwahlgravitation;
                _feldelektrostatisch<_tg>*anwahlfeldelektrostatisch;
                _feldmagnetostatisch<_tg>*anwahlfeldmagnetostatisch;
                _corundkugel*anwahlkugel;
                _corundknoten*anwahlknoten;

                _liste<_vertex> anwahlvertexliste;
                _liste<_polygon> anwahlpolygonliste;
                _liste<_verbindervertexpolygon> anwahlkanteliste;
                _liste<_netz> anwahlnetzliste;
                _liste<_licht<_tg,_to> > anwahllichtliste;
                _liste<_partikelquelle> anwahlpartikelquelleliste;
                _liste<_gravitation<_tg> > anwahlgravitationliste;
                _liste<_feldelektrostatisch<_tg> > anwahlfeldelektrostatischliste;
                _liste<_feldmagnetostatisch<_tg> > anwahlfeldmagnetostatischliste;
                _liste<_corundkugel> anwahlkugelliste;
                _liste<_corundknoten> anwahlknotenliste;

                //---------------- steinschablonen ------------
                _corundsteincorund*corundsteincorund;
                //---------------- baum kontrolle -------------
                bool baumzeichnen;
                //--------------- debug -----------------------
                bool debugintersektion;
                bool debugsektor;
                bool debugbsp;
                bool debugportal;
                bool debugsichtbarkeit;
};
//******************************************************************************************************************************************************************************************************
//                                                              H A U P T T O O L B A R
//******************************************************************************************************************************************************************************************************
class _haupttoolbar : public _guiwerkzeugleiste{
        public:
                _haupttoolbar(_hauptfenster*);
                virtual ~_haupttoolbar();
                void beinetzanwahl(_guiereignisdaten*);
                void beipolygonanwahl(_guiereignisdaten*);    
                void beikantenanwahl(_guiereignisdaten*);
                void beivertexanwahl(_guiereignisdaten*);
        public:                
                _hauptfenster*hauptfenster;
                _guiwerkzeugleisteknopf*netzanwahl;
                _guiwerkzeugleisteknopf*polygonanwahl;
                _guiwerkzeugleisteknopf*kantenanwahl;
                _guiwerkzeugleisteknopf*vertexanwahl;
};

#endif