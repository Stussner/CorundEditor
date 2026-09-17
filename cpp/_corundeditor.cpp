



#include "../hpp/_corundeditor.hpp"
#include "../hpp/_corundspeicherbar.hpp"

//#ifdef _DEBUG
// #define _CRTDBG_MAP_ALLOC
// #include <crtdbg.h>
//#endif
#include "../hpp/resource.h"

#include <_kommunikation.hpp>
#include <_editionigg.hpp>

class _testnetz;
class _testpolygon;
class _testvertex;
class _testverbindervertexpolygon;


class _testnetz:
public _listenknotenbasis<_testnetz >,
public _listebasis<_testpolygon >{
		public:
				_testnetz(){};
				virtual ~_testnetz(){};
};        

class _testpolygon:
public _listenknotenbasis<_testpolygon >,
public _vektor3<_tg>,
public _liste<_testvertex>{
public:
	using _liste<_testvertex>::naechstes;
		public:
                _testpolygon(_testnetz*n):_listenknotenbasis<_testpolygon>(n){};
                virtual ~_testpolygon(){};
		
};

class _testvertex:
public _vektor3<_tg>,
public _liste<_testpolygon>{
		public:
                _testvertex(){};
                virtual ~_testvertex(){};

};

class _testverbindervertexpolygon:
public _verbinder<_testvertex,_testpolygon>,
public _texturvektor<_tg>{
		public:
                _testverbindervertexpolygon(_testvertex*v,_testpolygon*p):_verbinder<_testvertex,_testpolygon>(p,v,v,p){};
                virtual ~_testverbindervertexpolygon(){};
};



//******************************************************************************************************************************************************************************************************
//                                                              H A U P T F E N S T E R 
//******************************************************************************************************************************************************************************************************
_hauptfenster::_hauptfenster(T_String<> const &pn):_guifensterhaupt(pn){


								_testnetz*tn=new _testnetz();
								_testpolygon*tp;
								tp=new _testpolygon(tn);
								_testvertex*tv;
								tv= new _testvertex();
								_testverbindervertexpolygon*tc;
								tc=new _testverbindervertexpolygon(tv,tp);


								//anwendung : polygon iteriert seine vertex und verbinder								
								_listenknoten<_testvertex>*lnvit;
								if(tp->anfang(lnvit))do{
								 _testverbindervertexpolygon*tc=static_cast<_testverbindervertexpolygon*>(lnvit);
								 
								}while(tp->naechstes(lnvit));
								
								//anwendung : vertex iteriert seine polygone und verbinder								
								_listenknoten<_testpolygon>*lnpit;
								if(tv->anfang(lnpit))do{
								 _testverbindervertexpolygon*tc=static_cast<_testverbindervertexpolygon*>(lnpit);
								 
								}while(tv->naechstes(lnpit));
								
								
								_iggsystem*iggsystem=new _iggsystem(this,800,600);
								delete iggsystem;









                                _guifenstersplash*splash;
                                splash=new _guifenstersplash(IDB_SPLASH); 
                                splash->zeigen();        

                                corundwelt=0;
                                rasterzeichnen=true;
                                rasterverwenden=true;
                                rasterbreite=8;
                                snapping=1;
                                testmodus=false;
                                baumzeichnen=false;
                                gfeldzeichnen=false;
                                efeldzeichnen=false;
                                bfeldzeichnen=false;
                                gfeldanzahl=10;
                                efeldanzahl=10;
                                bfeldanzahl=10;
                                debugintersektion=false;
                                debugsektor=false;
                                debugbsp=false;
                                debugportal=false;
                                debugsichtbarkeit=false;
                                
                                letzteanwahl=0;
                                loeschenanwahl();
                                tastatur=new _win::_tastatur();
                                //----------------------------- sound ----------------------------------------
                                // C_ConfigSection  *section;
                                // Read Configuration
                                //GLog.Open(L"Sound.log");
                                //if(!GConfig.Read(L"Sound.ini")) throw "soundinitialisierung : GConfig.read() fehlgeschlagen";
                                //if(!(section = GConfig.Section(L"Sound"))) throw "soundinitialisierung : GConfig.getSection() fehlgeschlagen";
                                //if(!LoadPackageAndClass(sound, section, L"Driver")) throw "soundinitialisierung : LoadPackageWithClass() fehlgeschlagen";
                                //sound->Init();
                                //sound=new I_Sound();//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                
                                akustik=new _akustikopenal();
                                L->schreiben("soundinit");
                                //------------------------------ texturen ------------------------------------
                                texturverwaltung=new _texturverwaltung<_tb>();
                                ladentexturen();
                                //------------------------------ samples und streams --------------------------
                                tonverwaltung=new _tonverwaltung(akustik);
                                ladensamples();
                                dummyganz=new _guifensterkind(this);
                                dummyganz->zeigen();
                                dummyoben=new _guifensterkind(dummyganz);
                                dummyoben->zeigen();
                                dummyunten=new _guifensterkind(dummyganz);
                                dummyunten->zeigen();
                                ansicht[0]=new _ansicht(this,dummyoben,"XZ");
                                ansicht[1]=new _ansicht(this,dummyoben,"XY");
                                ansicht[2]=new _ansicht(this,dummyunten,"YZ");
                                ansicht[3]=new _ansicht(this,dummyunten,"Kamera");
                               /* ansicht[0]->farbe.setzen(0,0,0,1);
                                ansicht[1]->farbe.setzen(0,0,0,1);
                                ansicht[2]->farbe.setzen(0,0,0,1);
                                ansicht[3]->farbe.setzen(0,0,0,1);*/
                                ansicht[0]->zeigen();
                                ansicht[1]->zeigen();
                                ansicht[2]->zeigen();
                                ansicht[3]->zeigen();
                                ansicht[0]->kamera->orthonormal(true);
                                ansicht[1]->kamera->orthonormal(true);
                                ansicht[2]->kamera->orthonormal(true);
                                ansicht[0]->kamera->groesse(100,100);
                                ansicht[1]->kamera->groesse(100,100);
                                ansicht[2]->kamera->groesse(100,100);
                                ansicht[0]->kamera->vektorebene0(_vektor3<_tg>(0,-1,0),_vektor3<_tg>(1,0,0));
                                ansicht[0]->istxz=true;
                                ansicht[0]->sichtkopplung0=ansicht[1];
                                ansicht[0]->sichtkopplung1=ansicht[2];
                                
                                ansicht[1]->kamera->vektorebene0(_vektor3<_tg>(0,0,1),_vektor3<_tg>(1,0,0));
                                ansicht[1]->istxy=true;
                                ansicht[1]->sichtkopplung0=ansicht[0];
                                ansicht[1]->sichtkopplung1=ansicht[2];
                                
                                ansicht[2]->kamera->vektorebene0(_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,-1));
                                ansicht[2]->istyz=true;
                                ansicht[2]->sichtkopplung0=ansicht[0];
                                ansicht[2]->sichtkopplung1=ansicht[1];
                                
                                ansicht[0]->cursor(IDC_CROSS);
                                ansicht[1]->cursor(IDC_CROSS);
                                ansicht[2]->cursor(IDC_CROSS);
                                ansicht[3]->cursor(IDC_CROSS);
                                ansicht[0]->grafik->aktivitaet(true);
                               // #ifdef CORUND_MIT_OPENGL
                                 ansicht[1]->grafik->gemeinsamedaten(ansicht[0]->grafik);
                                 ansicht[2]->grafik->gemeinsamedaten(ansicht[0]->grafik);
                                 ansicht[3]->grafik->gemeinsamedaten(ansicht[0]->grafik);
                                //#else
                               // #endif
                                splitterhorizontal=new _guiteilerhorizontal(dummyganz,dummyoben,dummyunten);
                                splitterhorizontal->zeigen();
                                splittervertikal[0] = new _guiteilervertikal(dummyoben,ansicht[0],ansicht[1]);
                                splittervertikal[1] = new _guiteilervertikal(dummyunten,ansicht[2],ansicht[3]);
                                splittervertikal[0]->zeigen(); 
                                splittervertikal[1]->zeigen(); 
                               // L->schreiben("spilttervertikal handle=",(int)splittervertikal[0]->handle());
                                *dummyoben += new _guiereignisSize<_hauptfenster>(this, &_hauptfenster::beigroessedummyoben);
                                *dummyunten += new _guiereignisSize<_hauptfenster>(this, &_hauptfenster::beigroessedummyunten);
                                tabwindow=new _guifensterkartei(this);
                                tabwindow->zeigen();
                                texturansicht=new _texturansicht(this,tabwindow);
                                L->schreiben("A");
                                //GUI::BCTabPage*tb=new GUI::BCTabPage(L"Textur",tabwindow);
                                new _guifensterkarteiseite(L"Sound",tabwindow);
                                L->schreiben("b");
                                toolbar=new _haupttoolbar(this);
                                toolbar->zeigen();
                                L->schreiben("C");
                                statusbar=new _guistatusleiste(this);
                                statusbar->zeigen();
                                bcInt32  parts[3]={90,200,-1};
                                statusbar->teile(3,parts);
                                L->schreiben("D");
                                
                                menubar=new _guimenueleiste();        
                                menueditor=new _guimenue(L"Editor");
                                
                                *menubar+=menueditor;
                                *menueditor += new _guimenueeintrag(L"&Hilfe", new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beinichtdefiniert)); 
                                L->schreiben("E");

                                *menueditor += new _guimenueeintrag(L"&Über", new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beinichtdefiniert)); 
                                *menueditor += new _guimenueeintrag(L"&Beenden   \tAlt+F4", new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beischliessen)); 
                                *menueditor += new _guimenueeintrag(L"&Konversion", new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beikonversion)); 
                                *menueditor += new _guimenueeintrag(L"&Eigenschaften", new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beieigenschaften)); 
                                menuwelt=new _guimenue(L"Welt");
                                *menubar+=menuwelt;
                                *menuwelt+=new _guimenueeintrag(L"Neu",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltneu)); 
                                *menuwelt+=new _guimenueeintrag(L"Laden",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltladen)); 
                                *menuwelt+=new _guimenueeintrag(L"Laden Hartgecodet",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltladenhart)); 
                                *menuwelt+=new _guimenueeintrag(L"Importieren",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltimportieren)); 
                                *menuwelt+=new _guimenueeintrag(L"Speichern",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltspeichern)); 
                                *menuwelt+=new _guimenueeintrag(L"Schließen",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltschliessen)); 
                                *menuwelt+=new _guimenueeintrag(L"Zonen vorerstellen",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltzonenvorerstellen)); 
                                *menuwelt+=new _guimenueeintrag(L"Zonen erstellen",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltzonenerstellen)); 
                                *menuwelt+=new _guimenueeintrag(L"Zonen löschen",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltzonenloeschen)); 
                                *menuwelt+=new _guimenueeintrag(L"Zonen bestrahlen",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltzonenbestrahlen)); 
                                *menuwelt+=new _guimenueeintrag(L"Testen (ohne Bestrahlung)",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiwelttestenohnebestrahlung)); 
                                *menuwelt+=new _guimenueeintrag(L"Testen",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiwelttesten)); 
                                *menuwelt+=new _guimenueeintrag(L"Testen des Weltverbundes",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiwelttestenverbund)); 
                                *menuwelt+=new _guimenueeintrag(L"Komplanare Netzflächen : nicht zeichnen",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltkomplanarenichtzeichnen)); 
                                *menuwelt+=new _guimenueeintrag(L"Komplanare Netzflächen : nicht kollidieren",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltkomplanarenichtkollidieren)); 
                                *menuwelt+=new _guimenueeintrag(L"Komplanare Netzflächen : keine Schattenwurf für Lightmaps",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiweltkomplanarekeinschattenwurflightmap)); 
                                *menuwelt+=new _guimenueeintrag(L"Eigenschaften",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiwelteigenschaften)); 

                                menuumgebung=new _guimenue(L"Umgebung");
                                *menubar+=menuumgebung;
                                *menuumgebung+=new _guimenueeintrag(L"Schwarz",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiumgebungschwarz)); 
                                *menuumgebung+=new _guimenueeintrag(L"Bergpanorama heiter",new _guiereignisCommand<_hauptfenster>(this, &_hauptfenster::beiumgebungbergpanoramaheiter)); 

                                menunetz=new _guimenue(L"Netz");
                                *menubar+=menunetz;
                                *menunetz+=new _guimenueeintrag(L"Rechtecknetz",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetznetz));
                                *menunetz+=new _guimenueeintrag(L"Scheibe",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetzscheibe));
                                *menunetz+=new _guimenueeintrag(L"Scheibe (trianguliert)",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menunetz+=new _guimenueeintrag(L"Scheibenabschnitt",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menunetz+=new _guimenueeintrag(L"Scheibenring",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menunetz+=new _guimenueeintrag(L"Scheibenring (trianguliert)",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menunetz+=new _guimenueeintrag(L"Quader",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetzquader));
                                *menunetz+=new _guimenueeintrag(L"Kreuz",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menunetz+=new _guimenueeintrag(L"Kreuzbalken",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetzkreuzbalken));
                                *menunetz+=new _guimenueeintrag(L"Raumkreuz",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menunetz+=new _guimenueeintrag(L"Zylinder",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetzzylinder));
                                *menunetz+=new _guimenueeintrag(L"Kugel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetzkugel));
                                *menunetz+=new _guimenueeintrag(L"Konus",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetzkonus));
                                *menunetz+=new _guimenueeintrag(L"Torus",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetztorus));
                                *menunetz+=new _guimenueeintrag(L"Hermitische Fläche",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinetzflaechehermite));
                                menustein=new _guimenue(L"Stein");
                                *menubar+=menustein;
                                *menustein+=new _guimenueeintrag(L"Normal",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinnormal));
                                *menustein+=new _guimenueeintrag(L"Corund",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteincorund));
                                *menustein+=new _guimenueeintrag(L"Gummiband",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteingummiband));
                                *menustein+=new _guimenueeintrag(L"Schere",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinschere));
                                *menustein+=new _guimenueeintrag(L"Verschiebbar",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinschieb));
                                *menustein+=new _guimenueeintrag(L"Boulder",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinboulder));
                                *menustein+=new _guimenueeintrag(L"Rotation",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinrotation));
                                *menustein+=new _guimenueeintrag(L"Impulsübertragung",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinimpuls));
                                *menustein+=new _guimenueeintrag(L"Elektrisch",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinelektrisch));
                                *menustein+=new _guimenueeintrag(L"Erdung",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinerdung));
                                *menustein+=new _guimenueeintrag(L"Beschleunigung",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinbeschleunigung));
                                *menustein+=new _guimenueeintrag(L"Totenkopf",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteintotenkopf));
                                *menustein+=new _guimenueeintrag(L"Tor",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteintor));
                                *menustein+=new _guimenueeintrag(L"Schalter",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinschalter));
                                *menustein+=new _guimenueeintrag(L"Kugelgenerator",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinkugelgen));
                                *menustein+=new _guimenueeintrag(L"Dach",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteindach));
                                *menustein+=new _guimenueeintrag(L"Flak",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinflak));
                                *menustein+=new _guimenueeintrag(L"Ausgang",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinausgang));
                                *menustein+=new _guimenueeintrag(L"Senker",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinsenker));
                                *menustein+=new _guimenueeintrag(L"Laser",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinlaser));
                                *menustein+=new _guimenueeintrag(L"Spiegel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinspiegel));
                                *menustein+=new _guimenueeintrag(L"Schloss", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinschloss));
                                *menustein+=new _guimenueeintrag(L"Ereignis", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinereignis));
                                *menustein+=new _guimenueeintrag(L"Gerisser Stein", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteingerissen));
                                *menustein+=new _guimenueeintrag(L"Spuckstein", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinspuck));
                                *menustein+=new _guimenueeintrag(L"Tauscher", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteintauscher));
                                *menustein+=new _guimenueeintrag(L"Magnetisch", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinmagnetisch));
                                *menustein+=new _guimenueeintrag(L"Dieb", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteindieb));
                                *menustein+=new _guimenueeintrag(L"Fliegengenerator", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinfliegengen));
                                *menustein+=new _guimenueeintrag(L"Spinnengenerator", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinspinnengen));
                                *menustein+=new _guimenueeintrag(L"Shogun", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinshogun));
                                *menustein+=new _guimenueeintrag(L"Puzzle", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinpuzzle));
                                *menustein+=new _guimenueeintrag(L"Gas", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteingas));
                                *menustein+=new _guimenueeintrag(L"Kombinationsschloss", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteinkombinationsschloss));
                                *menustein+=new _guimenueeintrag(L"Drehkreuz", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteindrehkreuz));                
                                *menustein+=new _guimenueeintrag(L"Einbahn", new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beisteineinbahn));                
                                
                                
                                
                                menuobjekt=new _guimenue(L"Objekt");
                                *menubar+=menuobjekt;
                                *menuobjekt+=new _guimenueeintrag(L"Ersatzkugel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektersatz));
                                *menuobjekt+=new _guimenueeintrag(L"Schlüssel A",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektschluessela));
                                *menuobjekt+=new _guimenueeintrag(L"Bombe",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektbombe));
                                *menuobjekt+=new _guimenueeintrag(L"Dynamit",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektdynamit));
                                *menuobjekt+=new _guimenueeintrag(L"Mine",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektmine));
                                *menuobjekt+=new _guimenueeintrag(L"Steinpille",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektsteinpille));
                                *menuobjekt+=new _guimenueeintrag(L"Alkohol",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektalkohol));
                                *menuobjekt+=new _guimenueeintrag(L"Bungeeseil",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektbungeeseil));
                                *menuobjekt+=new _guimenueeintrag(L"Schere",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektschere));
                                *menuobjekt+=new _guimenueeintrag(L"Zettel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektzettel));
                                *menuobjekt+=new _guimenueeintrag(L"Fallschirm",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektfallschirm));
                                *menuobjekt+=new _guimenueeintrag(L"Zauberstab",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektzauberstab));
                                *menuobjekt+=new _guimenueeintrag(L"Triebwerk",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjekttriebwerk));
                                *menuobjekt+=new _guimenueeintrag(L"Gesundheit",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektgesundheit));
                                *menuobjekt+=new _guimenueeintrag(L"Reisszwecke",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektreisszwecke));
                                *menuobjekt+=new _guimenueeintrag(L"Hammer",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjekthammer));
                                *menuobjekt+=new _guimenueeintrag(L"Gasbrenner",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektgasbrenner));
                                *menuobjekt+=new _guimenueeintrag(L"Schutzschild",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektschutzschild));
                                *menuobjekt+=new _guimenueeintrag(L"Schneidbrenner",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektschneidbrenner));
                                *menuobjekt+=new _guimenueeintrag(L"Schwarzesloch",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektschwarzesloch));
                                *menuobjekt+=new _guimenueeintrag(L"Magnet",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektmagnet));
                                *menuobjekt+=new _guimenueeintrag(L"Presslufthammer",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektpresslufthammer));
                                *menuobjekt+=new _guimenueeintrag(L"Teleporter",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektteleporter));
                                *menuobjekt+=new _guimenueeintrag(L"Gleitmittel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektgleitmittel));
                                *menuobjekt+=new _guimenueeintrag(L"Geld",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektgeld));
                                *menuobjekt+=new _guimenueeintrag(L"Sprungfeder",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektsprungfeder));
                                *menuobjekt+=new _guimenueeintrag(L"Skalierer",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektskalierer));
                                *menuobjekt+=new _guimenueeintrag(L"Pflanze",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektpflanze));
                                *menuobjekt+=new _guimenueeintrag(L"Obst",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektobst));
                                *menuobjekt+=new _guimenueeintrag(L"Dematerialisierung",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektdematerialisierung));
                                *menuobjekt+=new _guimenueeintrag(L"Devisualisierung",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektdevisualisierung));
                                *menuobjekt+=new _guimenueeintrag(L"Insektenspray",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektinsektenspray));
                                *menuobjekt+=new _guimenueeintrag(L"Feuerloescher",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektfeuerloescher));
                                *menuobjekt+=new _guimenueeintrag(L"Summer",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektsummer));
                                *menuobjekt+=new _guimenueeintrag(L"Blinker",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektblinker));
                                *menuobjekt+=new _guimenueeintrag(L"Batterie",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektbatterie));
                                *menuobjekt+=new _guimenueeintrag(L"Pinsel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektpinsel));
                                *menuobjekt+=new _guimenueeintrag(L"Besen",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektbesen));
                                *menuobjekt+=new _guimenueeintrag(L"Lampe",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektlampe));
                                *menuobjekt+=new _guimenueeintrag(L"Kerze",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektkerze));
                                *menuobjekt+=new _guimenueeintrag(L"Gewicht",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektgewicht));
                                *menuobjekt+=new _guimenueeintrag(L"Gasmaske",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektgasmaske));
                                *menuobjekt+=new _guimenueeintrag(L"Schutzhelm",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektschutzhelm));
                                *menuobjekt+=new _guimenueeintrag(L"Spritze",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiobjektspritze));  
                
                
                                menuboden=new _guimenue(L"Boden");
                                *menubar+=menuboden;                                
                                *menuboden+=new _guimenueeintrag(L"Normal",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodennormal));
                                *menuboden+=new _guimenueeintrag(L"Schalter",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodenschalter));
                                *menuboden+=new _guimenueeintrag(L"Invers",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodeninvers));
                                *menuboden+=new _guimenueeintrag(L"Weltraum",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodenweltraum));
                                *menuboden+=new _guimenueeintrag(L"Eis",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodeneis));
                                *menuboden+=new _guimenueeintrag(L"Sand",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodensand));
                                *menuboden+=new _guimenueeintrag(L"Schnee",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodenschnee));
                                *menuboden+=new _guimenueeintrag(L"Wiese",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodenwiese));
                                *menuboden+=new _guimenueeintrag(L"Wasser",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodenwasser));
                                *menuboden+=new _guimenueeintrag(L"Sumpf",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodensumpf));
                                *menuboden+=new _guimenueeintrag(L"Lava",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodenlava));
                                *menuboden+=new _guimenueeintrag(L"Beschleunigung",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodenbeschleunigung));
                                *menuboden+=new _guimenueeintrag(L"Gradienz",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodengradienz));
                                *menuboden+=new _guimenueeintrag(L"Transport",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodentransport));
                                *menuboden+=new _guimenueeintrag(L"Totenkopf",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibodentotenkopf));                                 
                                
                                
                                menufigur=new _guimenue(L"Figur");
                                *menubar+=menufigur;
                                *menufigur+=new _guimenueeintrag(L"Kugel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurkugel));
                                *menufigur+=new _guimenueeintrag(L"Spinne",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurspinne));
                                *menufigur+=new _guimenueeintrag(L"Springspinne",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurspringspinne));
                                *menufigur+=new _guimenueeintrag(L"Hebweber",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurhebweber));
                                *menufigur+=new _guimenueeintrag(L"Catwiesel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurcatwiesel));
                                *menufigur+=new _guimenueeintrag(L"Fliege",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurfliege));
                                *menufigur+=new _guimenueeintrag(L"Raupe",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurmade));
                                *menufigur+=new _guimenueeintrag(L"Orakel",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beifigurorakel));
                                *menufigur+=new _guimenueeintrag(L"Gummiband",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menufigur+=new _guimenueeintrag(L"Feder",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                menulicht=new _guimenue(L"Licht");
                                *menubar+=menulicht;
                                *menulicht+=new _guimenueeintrag(L"Licht",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beilichtlicht));
                                menuknoten=new _guimenue(L"Knoten");
                                *menubar+=menuknoten;
                                *menuknoten+=new _guimenueeintrag(L"Knoten",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiknotenknoten));
                                menugravitation=new _guimenue(L"Feld");
                                *menubar+=menugravitation;
                                *menugravitation+=new _guimenueeintrag(L"Gravitation",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beigravitation));
                                *menugravitation+=new _guimenueeintrag(L"Elektrisches Feld",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beiefeld));
                                *menugravitation+=new _guimenueeintrag(L"Magnetisches Feld",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beibfeld));
                                menupartikelquelle=new _guimenue(L"Partikelquelle");
                                *menupartikelquelle+=new _guimenueeintrag(L"Internen Standard anlegen",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beipartikelquelleintern));
                                *menupartikelquelle+=new _guimenueeintrag(L"Sprite",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beipartikelquellesprite));
                                *menubar+=menupartikelquelle;
                                menuaerodynamik=new _guimenue(L"Aerodynamik");
                                *menubar+=menuaerodynamik;
                                *menuaerodynamik+=new _guimenueeintrag(L"Windfeld",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                *menuaerodynamik+=new _guimenueeintrag(L"Thermische Konvektion",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                menufluiddynamik=new _guimenue(L"Fluiddynamik");
                                *menubar+=menufluiddynamik;
                                *menufluiddynamik+=new _guimenueeintrag(L"Wasser",new _guiereignisCommand<_hauptfenster>(this,&_hauptfenster::beinichtdefiniert));
                                menue(menubar);
                                menusound=new _guimenue(L"Sound");
                                *menubar+=menusound;
                                *this += new _guiereignisClose<_hauptfenster>(this, &_hauptfenster::beischliessen);
                                *this += new _guiereignisDestroy<_hauptfenster>(this, &_hauptfenster::beizerstoeren);
                                *this += new _guiereignisSize<_hauptfenster>(this, &_hauptfenster::beigroesse);
                                L->schreiben("ASTa");
                                
                                dyndialog=new _corunddialog(this,L"Allgemein",this);
                                dhart=new _dialoghart(this,this);
                                
                                dtexturgeometrie=new _dialogtexturgeometrie(this,this);  L->schreiben("ASTs");
                                dlicht=new _dialoglicht(this,L"Licht konstruieren",this);
                                dbiegen=new _dialogbiegen(this,L"Netz verbiegen",this);
                                drotieren=new _dialogrotieren(this,L"Netz rotieren",this);
                                dverdrehen=new _dialogverdrehen(this,L"Netz verdrehen",this);
                                dumgebung=new _dialogumgebung(this,L"Umgebung konstruieren",this);
                               
                                splash->zeigen();    
                                dknoten=new _dialogknoten(this,L"Knoten konstruieren",this);
                                dfraktal=new _dialogfraktal(this,L"Fraktal auf Netz abbilden",this);
                                dkugel=new _dialogkugel(this,L"Kugel konstruieren",this);
                                dspinne=new _dialogspinne(this,L"Spinne konstruieren",this);
                                dorakel=new _dialogfigur<_corundorakel>(this,L"Orakel konstruieren",this);
                                dspringspinne=new _dialogfigur<_corundspringspinne>(this,L"Springspinne konstruieren",this);
                                dhebweber=new _dialogfigur<_corundhebweber>(this,L"Hebweber konstruieren",this);
                                dcatwiesel=new _dialogfigur<_corundcatwiesel>(this,L"Catwiesel konstruieren",this);
                                dfliege=new _dialogfigur<_corundfliege>(this,L"Fliege konstruieren",this);
                                dmade=new _dialogfigur<_corundmade>(this,L"Raupe konstruieren",this);
                               
                                dsteinnormal=new _dialogstein<_corundstein>(this,L"Normalen Stein konstruieren",this);
                                dsteincorund=new _dialogstein<_corundsteincorund>(this,L"corundstein konstruieren",this);
                                dsteingummiband=new _dialogstein<_corundsteingummiband>(this,L"Gummibandstein konstruieren",this);
                                dsteinschere=new _dialogstein<_corundsteinschere>(this,L"Scherenstein konstruieren",this);
                                dsteinschieb=new _dialogstein<_corundsteinschieb>(this,L"Verschiebbaren Stein konstruieren",this);
                                dsteinboulder=new _dialogstein<_corundsteinboulder>(this,L"Boulderstein konstruieren",this);
                                dsteinrotation=new _dialogstein<_corundsteinrotation>(this,L"Rotationsstein konstruieren",this);
                                dsteinimpuls=new _dialogstein<_corundsteinimpuls>(this,L"Impulsübertragungsstein konstruieren",this);
                                dsteinelektrisch=new _dialogstein<_corundsteinelektrisch>(this,L"Elektrischen Stein konstruieren",this);
                                dsteinerdung=new _dialogstein<_corundsteinerdung>(this,L"Erdungsstein konstruieren",this);
                                dsteinbeschleunigung=new _dialogstein<_corundsteinbeschleunigung>(this,L"Beschleunigungsstein konstruieren",this);
                                dsteintotenkopf=new _dialogstein<_corundsteintotenkopf>(this,L"Totenkopfstein konstruieren",this);
                                dsteintor=new _dialogstein<_corundsteintor>(this,L"Torstein konstruieren",this);
                                dsteinschalter=new _dialogstein<_corundsteinschalter>(this,L"Schalterstein konstruieren",this);
                                dsteinkugelgen=new _dialogstein<_corundsteinkugelgen>(this,L"Kugelgeneratorstein konstruieren",this);
                                dsteindach=new _dialogstein<_corundsteindach>(this,L"Dachstein konstruieren",this);
                                dsteinflak=new _dialogstein<_corundsteinflak>(this,L"Flakstein konstruieren",this);
                                dsteinausgang=new _dialogstein<_corundsteinausgang>(this,L"Ausgang konstruieren",this);
                                dsteinsenker=new _dialogstein<_corundsteinsenker>(this,L"Senker konstruieren",this);
                                dsteinlaser=new _dialogstein<_corundsteinlaser>(this,L"Laser konstruieren",this);
                                dsteinspiegel=new _dialogstein<_corundsteinspiegel>(this,L"Spiegel konstruieren",this);
                                dsteinschloss=new _dialogstein<_corundsteinschloss>(this,L"Schloss konstruieren",this);
                                dsteinereignis=new _dialogstein<_corundsteinereignis>(this,L"Ereignis konstruieren",this);
                                dsteingerissen=new _dialogstein<_corundsteingerissen>(this,L"Gerissenen Stein konstruieren",this);
                                dsteinspuck=new _dialogstein<_corundsteinspuck>(this,L"Spuckstein konstruieren",this);
                                dsteintauscher=new _dialogstein<_corundsteintauscher>(this,L"Tauscher konstruieren",this);
                                dsteinmagnetisch=new _dialogstein<_corundsteinmagnetisch>(this,L"Magnetischen Stein konstruieren",this);
                                dsteindieb=new _dialogstein<_corundsteindieb>(this,L"Diebstein konstruieren",this);
                                dsteinfliegengen=new _dialogstein<_corundsteinfliegengen>(this,L"Fliegengeneratorstein konstruieren",this);
                                dsteinspinnengen=new _dialogstein<_corundsteinspinnengen>(this,L"Spinnengeneratorstein konstruieren",this);
                                dsteinshogun=new _dialogstein<_corundsteinshogun>(this,L"Shogunstein konstruieren",this);
                                dsteinpuzzle=new _dialogstein<_corundsteinpuzzle>(this,L"Puzzlestein konstruieren",this);
                                dsteingas=new _dialogstein<_corundsteingas>(this,L"Gasstein konstruieren",this);
                                dsteinkombinationsschloss=new _dialogstein<_corundsteinkombinationsschloss>(this,L"Kombinationsschloss konstruieren",this);
                                dsteindrehkreuz=new _dialogstein<_corundsteindrehkreuz>(this,L"Drehkreuz konstruieren",this);                
                                dsteineinbahn=new _dialogstein<_corundsteineinbahn>(this,L"Einbahn konstruieren",this);                
                                
                               
                                dobjektersatz=new _dialogobjekt<_corundobjektersatz>(this,L"Ersatzkugel konstruieren",this);
                                dobjektschluessela=new _dialogobjekt<_corundobjektschluessela>(this,L"Schlüssel A konstruieren",this);
                                dobjektbombe=new _dialogobjekt<_corundobjektbombe>(this,L"Bombe konstruieren",this);
                                dobjektdynamit=new _dialogobjekt<_corundobjektdynamit>(this,L"Dynamit konstruieren",this);
                                dobjektmine=new _dialogobjekt<_corundobjektmine>(this,L"Mine konstruieren",this);
                                dobjektsteinpille=new _dialogobjekt<_corundobjektsteinpille>(this,L"Steinpille konstruieren",this);
                                dobjektalkohol=new _dialogobjekt<_corundobjektalkohol>(this,L"Alkohol konstruieren",this);
                                dobjektbungeeseil=new _dialogobjekt<_corundobjektbungeeseil>(this,L"Bungeeseil konstruieren",this);
                                dobjektschere=new _dialogobjekt<_corundobjektschere>(this,L"Schere konstruieren",this);
                                dobjektzettel=new _dialogobjekt<_corundobjektzettel>(this,L"Zettel konstruieren",this);
                                dobjektfallschirm=new _dialogobjekt<_corundobjektfallschirm>(this,L"Fallschirm konstruieren",this);
                                dobjektzauberstab=new _dialogobjekt<_corundobjektzauberstab>(this,L"Zauberstab konstruieren",this);
                                dobjekttriebwerk=new _dialogobjekt<_corundobjekttriebwerk>(this,L"Triebwerk konstruieren",this);
                                dobjektgesundheit=new _dialogobjekt<_corundobjektgesundheit>(this,L"Gesundheit konstruieren",this);
                                dobjektreisszwecke=new _dialogobjekt<_corundobjektreisszwecke>(this,L"Reisszwecke konstruieren",this);
                                dobjekthammer=new _dialogobjekt<_corundobjekthammer>(this,L"Hammer konstruieren",this);
                                dobjektgasbrenner=new _dialogobjekt<_corundobjektgasbrenner>(this,L"Gasbrenner konstruieren",this);
                                dobjektschutzschild=new _dialogobjekt<_corundobjektschutzschild>(this,L"Schutzschild konstruieren",this);
                                dobjektschneidbrenner=new _dialogobjekt<_corundobjektschneidbrenner>(this,L"Schneidbrenner konstruieren",this); 
                                dobjektschwarzesloch=new _dialogobjekt<_corundobjektschwarzesloch>(this,L"Schwarzesloch konstruieren",this);
                                dobjektmagnet=new _dialogobjekt<_corundobjektmagnet>(this,L"Magnet konstruieren",this);
                                dobjektpresslufthammer=new _dialogobjekt<_corundobjektpresslufthammer>(this,L"Presslufthammer konstruieren",this);
                                dobjektteleporter=new _dialogobjekt<_corundobjektteleporter>(this,L"Teleporter konstruieren",this);
                                dobjektgleitmittel=new _dialogobjekt<_corundobjektgleitmittel>(this,L"Gleitmittel konstruieren",this);
                                dobjektgeld=new _dialogobjekt<_corundobjektgeld>(this,L"Geld konstruieren",this);
                                dobjektsprungfeder=new _dialogobjekt<_corundobjektsprungfeder>(this,L"Sprungfeder konstruieren",this);
                                dobjektskalierer=new _dialogobjekt<_corundobjektskalierer>(this,L"Skalierer konstruieren",this);
                                dobjektpflanze=new _dialogobjekt<_corundobjektpflanze>(this,L"Pflanze konstruieren",this);
                                dobjektobst=new _dialogobjekt<_corundobjektobst>(this,L"Obst konstruieren",this);
                                dobjektdematerialisierung=new _dialogobjekt<_corundobjektdematerialisierung>(this,L"Dematerialisierung konstruieren",this);
                                dobjektdevisualisierung=new _dialogobjekt<_corundobjektdevisualisierung>(this,L"Devisualisierung konstruieren",this);
                                dobjektinsektenspray=new _dialogobjekt<_corundobjektinsektenspray>(this,L"Insektenspray konstruieren",this);
                                dobjektfeuerloescher=new _dialogobjekt<_corundobjektfeuerloescher>(this,L"Feuerlöscher konstruieren",this);
                                dobjektsummer=new _dialogobjekt<_corundobjektsummer>(this,L"Summer konstruieren",this);
                                dobjektblinker=new _dialogobjekt<_corundobjektblinker>(this,L"Blinker konstruieren",this);
                                dobjektbatterie=new _dialogobjekt<_corundobjektbatterie>(this,L"Batterie konstruieren",this);
                                dobjektpinsel=new _dialogobjekt<_corundobjektpinsel>(this,L"Pinsel konstruieren",this);
                                dobjektbesen=new _dialogobjekt<_corundobjektbesen>(this,L"Besen konstruieren",this);
                                dobjektlampe=new _dialogobjekt<_corundobjektlampe>(this,L"Lampe konstruieren",this);
                                dobjektkerze=new _dialogobjekt<_corundobjektkerze>(this,L"Kerze konstruieren",this);
                                dobjektgewicht=new _dialogobjekt<_corundobjektgewicht>(this,L"Gewicht konstruieren",this);
                                dobjektgasmaske=new _dialogobjekt<_corundobjektgasmaske>(this,L"Gasmaske konstruieren",this);
                                dobjektschutzhelm=new _dialogobjekt<_corundobjektschutzhelm>(this,L"Schutzhelm konstruieren",this);
                                dobjektspritze=new _dialogobjekt<_corundobjektspritze>(this,L"Spritze konstruieren",this);                                  
                                
                                dbodennormal=new _dialogboden<_corundbodennormal>(this,L"Normalen Boden konstruieren",this);
                                dbodenschalter=new _dialogboden<_corundbodenschalter>(this,L"Bodenschalter konstruieren",this);
                                dbodeninvers=new _dialogboden<_corundbodeninvers>(this,L"Inversen Boden konstruieren",this);
                                dbodenweltraum=new _dialogboden<_corundbodenweltraum>(this,L"Weltraumboden konstruieren",this);
                                dbodeneis=new _dialogboden<_corundbodeneis>(this,L"Eis konstruieren",this);
                                dbodensand=new _dialogboden<_corundbodensand>(this,L"Sand konstruieren",this);
                                dbodenschnee=new _dialogboden<_corundbodenschnee>(this,L"Schnee konstruieren",this);
                                dbodenwiese=new _dialogboden<_corundbodenwiese>(this,L"Wiese konstruieren",this);
                                dbodenwasser=new _dialogboden<_corundbodenwasser>(this,L"Wasser konstruieren",this);
                                dbodensumpf=new _dialogboden<_corundbodensumpf>(this,L"Sumpf konstruieren",this);
                                dbodenlava=new _dialogboden<_corundbodenlava>(this,L"Lava konstruieren",this);
                                dbodenbeschleunigung=new _dialogboden<_corundbodenbeschleunigung>(this,L"Beschleunigungsboden konstruieren",this);
                                dbodengradienz=new _dialogboden<_corundbodengradienz>(this,L"Gradienten Boden konstruieren",this);
                                dbodentransport=new _dialogboden<_corundbodentransport>(this,L"Transportboden konstruieren",this);
                                dbodentotenkopf=new _dialogboden<_corundbodentotenkopf>(this,L"Totenkopfboden konstruieren",this);                                 
                                
                                
                                dknotenwahl=new _dialogknotenwahl(this,this);
                                dnetzwahl=new _dialognetzwahl(this,this);
                                dfigurwahl=new _dialogfigurwahl(this,this);
                                dsteincorundschaltkopplungswahl=new _dialogschaltkopplungwahl<_corundsteincorund>(this,this);
                                dsteinereignisschaltkopplungswahl=new _dialogschaltkopplungwahl<_corundsteinereignis>(this,this);
                                dsteinschlossschaltkopplungswahl=new _dialogschaltkopplungwahl<_corundsteinschloss>(this,this);
                                dsteinschaltkopplungswahl=new _dialogschaltkopplungwahl<_corundsteinschalter>(this,this);
                                dbodenschaltkopplungswahl=new _dialogschaltkopplungwahl<_corundbodenschalter>(this,this);
                                
                                dgravitation=new _dialoggravitation(this,L"Gravitation konstruieren",this);
                                dfeldelektrostatisch=new _dialogfeldelektrostatisch(this,L"elektrostatisches Feld konstruieren",this);
                                dfeldmagnetostatisch=new _dialogfeldmagnetostatisch(this,L"magnetostatisches Feld konstruieren",this);
                                dpartikelquellesprite=new _dialogpartikelquellesprite(this,L"Partikelquellesprite konstruieren",this);
                                gquader=new _geometriequader(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),0);
                                dquader=new _dialoggeometrie<_geometriequader>(this,gquader,L"Quader konstruieren",this);
                                gquader->einhaengendialog(dquader);

                                gkreuzbalken=new _geometriekreuzbalken(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(16,0,0),_vektor3<_tg>(0,16,0),_vektor3<_tg>(0,0,8),0.16,0);
                                dkreuzbalken=new _dialoggeometrie<_geometriekreuzbalken>(this,gkreuzbalken,L"Kreuzbalken konstruieren",this);
                                gkreuzbalken->einhaengendialog(dkreuzbalken);


                                gnetz=new _geometrienetz(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,1),0);
                                dnetz=new _dialoggeometrie<_geometrienetz>(this,gnetz,L"Netz konstruieren",this);
                                gnetz->einhaengendialog(dnetz);
                                
                                gscheibe=new _geometriescheibe(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,1),0);
                                dscheibe=new _dialoggeometrie<_geometriescheibe>(this,gscheibe,L"Scheibe konstruieren",this);
                                gscheibe->einhaengendialog(dscheibe);
                                
                                gzylinder=new _geometriezylinder(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,1),0);
                                dzylinder=new _dialoggeometrie<_geometriezylinder>(this,gzylinder,L"Zylinder konstruieren",this);
                                gzylinder->einhaengendialog(dzylinder);
                                gkonus=new _geometriekonus(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),0);
                                dkonus=new _dialoggeometrie<_geometriekonus>(this,gkonus,L"Konus konstruieren",this);
                                gkonus->einhaengendialog(dkonus);
                                gkugel=new _geometriekugel(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),0);
                                dgkugel=new _dialoggeometrie<_geometriekugel>(this,gkugel,L"Kugel konstruieren",this);
                                gkugel->einhaengendialog(dgkugel);
                                gtorus=new _geometrietorus(this,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,1,0),_vektor3<_tg>(0,0,1),0.2,0.2,0);
                                dtorus=new _dialoggeometrie<_geometrietorus>(this,gtorus,L"Torus konstruieren",this);
                                gtorus->einhaengendialog(dtorus);
                                gflaechehermite=new _geometrieflaechehermite(this,0);
                                dflaechehermite=new _dialoggeometrie<_geometrieflaechehermite>(this,gflaechehermite,L"Hermitische Fläche konstruieren",this);
                                gflaechehermite->einhaengendialog(dflaechehermite);
                                
                                zentrieren(900, 700, false);
                                maximieren();                                
								//tonverwaltung->tonfluss(0)->abspielen();
                                //------------------- stein konstruktionsschablonen -------------------------------
                                corundsteincorund=new _corundsteincorund(0,0,0,0,1,1,1,texturverwaltung->textur((unsigned int)0),0);
                                delete splash;
};
_hauptfenster::~_hauptfenster(){
                                delete corundsteincorund;
                                _listebasis<_geometrie>::loeschen();
                                delete texturverwaltung;
                                delete tonverwaltung;
                                deletesecure(akustik);  
                                deletesecure(tastatur);
};
void _hauptfenster::ladensamples(){
                                tonverwaltung->erzeugenton(0,"ton/raul.ogg");
                                tonverwaltung->erzeugenton(1,"ton/bassdfuthal.ogg");
                                tonverwaltung->erzeugenton(2,"ton/btom1.ogg");
                                tonverwaltung->erzeugenton(3,"ton/schuss_001_mod.ogg");
                                tonverwaltung->erzeugenton(4,"ton/explosion1.ogg");
                                tonverwaltung->erzeugenton(5,"ton/explosion2.ogg");
                                tonverwaltung->erzeugenton(6,"ton/laserein.ogg");
                                tonverwaltung->erzeugenton(7,"ton/spiegeldreh.ogg");
                                tonverwaltung->erzeugenton(8,"ton/lachen04.ogg");
                                tonverwaltung->erzeugenton(9,"ton/lachen05.ogg");
                                tonverwaltung->erzeugenton(10,"ton/lachen06.ogg");
                                //tonverwaltung->erzeugentonfluss(0,"musik/06. Track06.ogg");
};
void _hauptfenster::ladentexturen(){
                                //textur=new _texturverwaltung<>();
                                ladentextur(0,"textur//corundbodenplatte00.tga",true);
                                ladentextur(1,"textur//fragezeichen.tga",true);
                                ladentextur(2,"textur//corundbodenplatteniete02.tga",true);
                                ladentextur(3,"textur//schwarz.tga",true);
                                ladentextur(4,"textur//feuer01.tga",true);
                                ladentextur(5,"textur//brick02b.tga",true);
                                ladentextur(6,"textur//brick00.tga",true);
                                ladentextur(7,"textur//marmor02.tga",true);
                                ladentextur(8,"textur//coron01.tga",true);
                                ladentextur(9,"textur//sgmarmor00.tga",true);
                                ladentextur(10,"textur//sgmarmor00rand.tga",true);
                                ladentextur(11,"textur//floor08.tga",true);
                                ladentextur(12,"textur//marble08gummiband.tga",true);
                                ladentextur(13,"textur//marble08schereoffen.tga",true);
                                ladentextur(14,"textur//marble08scherezu.tga",true);
                                ladentextur(15,"textur//coron08.tga",true);
                                ladentextur(16,"textur//coron06rot.tga",true);
                                ladentextur(17,"textur//skybox1_down.tga",true);
                                ladentextur(18,"textur//skybox1_up.tga",true);
                                ladentextur(19,"textur//skybox1_left.tga",true);
                                ladentextur(20,"textur//skybox1_right.tga",true);
                                ladentextur(21,"textur//skybox1_front.tga",false);
                                ladentextur(22,"textur//skybox1_back.tga",false);
                                ladentextur(23,"textur//corundsteincorund.tga",true);
                                ladentextur(24,"textur//corundsteincorund00offen.tga",true);
                                ladentextur(25,"textur//corundsteincorund01offen.tga",true);
                                ladentextur(26,"textur//corundsteincorund02offen.tga",true);
                                ladentextur(27,"textur//metallmikro01.tga",true);
                                ladentextur(28,"textur//granit0.tga",true);
                                ladentextur(29,"textur//muendung01.tga",false);
                                ladentextur(30,"textur//muendung02.tga",false);
                                ladentextur(31,"textur//corundbodenplatte02.tga",true);
                                ladentextur(32,"textur//corundsteinimpuls00.tga",false);
                                ladentextur(33,"textur//corundsteinimpuls01.tga",false);
                                ladentextur(34,"textur//corundsteinimpuls02.tga",false);
                                ladentextur(35,"textur//corundsteinimpuls03.tga",false);
                                ladentextur(36,"textur//corundsteinimpuls04.tga",false);
                                ladentextur(37,"textur//corundsteinimpuls05.tga",false);
                                ladentextur(38,"textur//corundsteinimpuls06.tga",false);
                                ladentextur(39,"textur//corundlaser.tga",false);
                                ladentextur(40,"textur//fragezeichen.tga",false);
                                ladentextur(41,"textur//corundwandwarn00.tga",true);
                                ladentextur(42,"textur//corundwandwarn01.tga",true);
                                ladentextur(43,"textur//corundwandwarn02.tga",true);
                                ladentextur(44,"textur//corundlochwand00.tga",true);
                                ladentextur(45,"textur//corundlasermagenta.tga",false);
                                ladentextur(46,"textur//corundlasergruen.tga",false);
                                ladentextur(47,"textur//corundlaserorange.tga",false);
                                ladentextur(48,"textur//dynamit.tga",true);
                                ladentextur(49,"textur//mine.tga",true);
                                ladentextur(50,"textur//marble08.tga",true);
                                ladentextur(51,"textur//seil.tga",true);
                                ladentextur(52,"textur//zettel.tga",true);
                                ladentextur(53,"textur//wasser00.tga",true);
                                ladentextur(54,"textur//springspinne00.tga",false);
                                ladentextur(55,"textur//corundsteineinbahno.tga",true);
                                ladentextur(56,"textur//corundsteineinbahns.tga",true);
                                ladentextur(57,"textur//corundsteineinbahnw.tga",true);
                                ladentextur(58,"textur//corundsteineinbahnn.tga",true);
                                ladentextur(59,"textur//corundsteineinbahnverbot.tga",true);
                                ladentextur(60,"textur//corundboulderoben00.tga",true);
                                ladentextur(61,"textur//corundboulderoben01.tga",true);
                                ladentextur(62,"textur//corundboulderrechts00.tga",true);
                                ladentextur(63,"textur//corundboulderrechts01.tga",true);
                                ladentextur(64,"textur//corundboulderunten00.tga",true);
                                ladentextur(65,"textur//corundboulderunten01.tga",true);
                                ladentextur(66,"textur//corundboulderlinks00.tga",true);
                                ladentextur(67,"textur//corundboulderlinks01.tga",true);
                                ladentextur(68,"textur//corundschablone01.tga",true);
                                ladentextur(69,"textur//corundrotationlinks.tga",true);
                                ladentextur(70,"textur//corundrotationrechts.tga",true);
                                ladentextur(71,"textur//corundsteineplus00.tga",true);
                                ladentextur(72,"textur//corundsteineplus01.tga",true);
                                ladentextur(73,"textur//corundsteineminus00.tga",true);
                                ladentextur(74,"textur//corundsteineminus01.tga",true);
                                ladentextur(75,"textur//corundsteinerdung00.tga",true);
                                ladentextur(76,"textur//corundsteinerdung01.tga",true);
                                ladentextur(77,"textur//corundsteinimpuls.tga",true);
                                ladentextur(78,"textur//corundschieber00.tga",true);
                                ladentextur(79,"textur//corundschieber01.tga",true);
                                ladentextur(80,"textur//corundschalter00aus.tga",true);
                                ladentextur(81,"textur//corundschalter00ein.tga",true);
                                ladentextur(82,"textur//corundsteintotenkopf00.tga",true);
                                ladentextur(83,"textur//corundsteintotenkopf01.tga",true);
                                ladentextur(84,"textur//corundsteinloch.tga",true);
                                ladentextur(85,"textur//riss00.tga",true);
                                ladentextur(86,"textur//riss01.tga",true);
                                ladentextur(87,"textur//riss02.tga",true);
                                ladentextur(88,"textur//riss03.tga",true);
                                ladentextur(89,"textur//riss04.tga",true);
                                ladentextur(90,"textur//riss05.tga",true);
                                ladentextur(91,"textur//holz00.tga",true);
                                ladentextur(92,"textur//corundschloss00.tga",true);
                                ladentextur(93,"textur//corundschloss01.tga",true);
                                ladentextur(94,"textur//gold00.tga",true);
                                ladentextur(95,"textur//gitter00.tga",true);
                                ladentextur(96,"textur//brick01.tga",true);
                                ladentextur(97,"textur//gitter01.tga",true);
                                ladentextur(98,"textur//buntglas01.tga",true);
                                ladentextur(99,"textur//fassade00.tga",true);
                                ladentextur(100,"textur//schiefer00.tga",true);
                                ladentextur(101,"textur//marmorgrau.tga",true);
                                ladentextur(102,"textur//marmorweiss.tga",true);
                                ladentextur(103,"textur//rostkachel_512.tga",true);
                                ladentextur(104,"textur//holzrauh.tga",true);
                                ladentextur(105,"textur//buergersteig00.tga",true);
                                ladentextur(106,"textur//steine00.jpg",true);
                                ladentextur(107,"textur//erde00.jpg",true);
                                ladentextur(108,"textur//mauer00.jpg",true);
                                ladentextur(109,"textur//mauer01.jpg",true);
                                ladentextur(110,"textur//mauer02.jpg",true);
                                ladentextur(111,"textur//mauer03.jpg",true);
                                ladentextur(112,"textur//gras03.jpg",true);
                                ladentextur(113,"textur//gras04.jpg",true);
                                ladentextur(114,"textur//fenster00.jpg",true);
                                ladentextur(115,"textur//fenster01.jpg",true);
                                ladentextur(116,"textur//metall01.jpg",true);
                                ladentextur(117,"textur//metall02.jpg",true);
                                ladentextur(118,"textur//holothelevorderleib.jpg",true);
                                ladentextur(119,"textur//holothelehinterleib.jpg",true);
                                ladentextur(120,"textur//psalmopoeusbein.jpg",true);
                                ladentextur(121,"textur//fenster03.jpg",true);
                                ladentextur(122,"textur//fenster04.jpg",true);
                                ladentextur(123,"textur//fenster05.jpg",true);
                                ladentextur(124,"textur//fenster06.jpg",true);
                                ladentextur(125,"textur//fenster07.jpg",true);
                                ladentextur(126,"textur//fenster08.jpg",true);
                                ladentextur(127,"textur//fenster09.jpg",true);
                                ladentextur(128,"textur//fenster10.jpg",true);
                                ladentextur(129,"textur//fenster11.jpg",true);
                                ladentextur(130,"textur//fenster12.jpg",true);
                                ladentextur(131,"textur//fenster13.jpg",true);
                                ladentextur(132,"textur//fenster14.jpg",true);
                                ladentextur(133,"textur//fenster15.jpg",true);
                                ladentextur(134,"textur//fenster16.jpg",true);
                                ladentextur(135,"textur//fenster17.jpg",true);
                                ladentextur(136,"textur//fenster18.jpg",true);
                                ladentextur(137,"textur//fenster19.jpg",true);
                                ladentextur(138,"textur//fenster20.jpg",true);
                                ladentextur(139,"textur//fenster21.jpg",true);
                                ladentextur(140,"textur//fenster22.jpg",true);
                                ladentextur(141,"textur//fenster23.jpg",true);
                                ladentextur(142,"textur//fenster24.jpg",true);
                                ladentextur(143,"textur//fenster25.jpg",true);
                                ladentextur(144,"textur//fenster26.jpg",true);
                                ladentextur(145,"textur//fenster27.jpg",true);
                                ladentextur(146,"textur//fenster28.jpg",true);

                                ladentextur(147,"textur//dach00.jpg",true);
                                ladentextur(148,"textur//dach01.jpg",true);
                                ladentextur(149,"textur//dach02.jpg",true);
                                ladentextur(150,"textur//dach03.jpg",true);
                                ladentextur(151,"textur//dach04.jpg",true);
                                ladentextur(152,"textur//dach05.jpg",true);
                                ladentextur(153,"textur//dach06.jpg",true);
                                ladentextur(154,"textur//dach07.jpg",true);
                                ladentextur(155,"textur//dach08.jpg",true);
                                ladentextur(156,"textur//dach09.jpg",true);
                                ladentextur(157,"textur//dach10.jpg",true);
                                ladentextur(158,"textur//dach11_512.jpg",true);
                                ladentextur(159,"textur//dach12.jpg",true);
                                ladentextur(160,"textur//dach13.jpg",true);
                                
                              //  ladentextur(0,"textur//dach14.jpg",true);
                              //  ladentextur(0,"textur//dach15.jpg",true);
                                ladentextur(0,"textur//dach16.jpg",true);
                                //ladentextur(0,"textur//dach17.jpg",true);
                                ladentextur(0,"textur//dach18.jpg",true);
                                ladentextur(0,"textur//dach19.jpg",true);
                                ladentextur(0,"textur//dach20.jpg",true);
                                ladentextur(0,"textur//dach21.jpg",true);
                                ladentextur(0,"textur//dach22.jpg",true);
                                ladentextur(0,"textur//dach23.jpg",true);
                                ladentextur(0,"textur//dach24.jpg",true);
                                ladentextur(0,"textur//dach25.jpg",true);
                                //ladentextur(0,"textur//dach26.jpg",true);
                                ladentextur(0,"textur//dach27.jpg",true);
                                ladentextur(0,"textur//dach28.jpg",true);
                                ladentextur(0,"textur//dach29.jpg",true);
                                ladentextur(0,"textur//dach30.jpg",true);
                                ladentextur(0,"textur//dach31.jpg",true);
                                ladentextur(0,"textur//dach32.jpg",true);
                                ladentextur(0,"textur//dach33.jpg",true);
                                ladentextur(0,"textur//dach34.jpg",true);
                                ladentextur(0,"textur//dach35.jpg",true);
                                ladentextur(0,"textur//dach36.jpg",true);
                                ladentextur(0,"textur//dach37.jpg",true);
                                ladentextur(0,"textur//dach38.jpg",true);
                                ladentextur(0,"textur//dach39.jpg",true);
                                ladentextur(0,"textur//dach40.jpg",true);
                                ladentextur(0,"textur//dach41.jpg",true);
                                ladentextur(0,"textur//dach42.jpg",true);
                                ladentextur(0,"textur//dach43.jpg",true);
                                ladentextur(0,"textur//dach44.jpg",true);

                                ladentextur(0,"textur//brick03.jpg",true);
                                ladentextur(0,"textur//brick04.jpg",true);
                                ladentextur(0,"textur//brick05.jpg",true);
                                ladentextur(0,"textur//brick06.jpg",true);
                                ladentextur(0,"textur//brick07.jpg",true);
                                ladentextur(0,"textur//brick08.jpg",true);
                                ladentextur(0,"textur//brick09.jpg",true);
                                ladentextur(0,"textur//brick10.jpg",true);
                                ladentextur(0,"textur//brick11.jpg",true);
                                ladentextur(0,"textur//brick12.jpg",true);
                                ladentextur(0,"textur//brick13.jpg",true);
                                ladentextur(0,"textur//brick14.jpg",true);
                                ladentextur(0,"textur//brick15.jpg",true);
                                ladentextur(0,"textur//brick16.jpg",true);
                                ladentextur(0,"textur//brick17.jpg",true);
                                ladentextur(0,"textur//brick18.jpg",true);
                                ladentextur(0,"textur//brick19.jpg",true);
                                ladentextur(0,"textur//brick20_512.jpg",true);
                                ladentextur(0,"textur//brick21.jpg",true);
                                ladentextur(0,"textur//brick22.jpg",true);
                                ladentextur(0,"textur//brick23.jpg",true);
                                ladentextur(0,"textur//brick24.jpg",true);
                                ladentextur(0,"textur//brick25.jpg",true);
                                ladentextur(0,"textur//brick26.jpg",true);
                                ladentextur(0,"textur//brick27.jpg",true);
                                ladentextur(0,"textur//brick28.jpg",true);
                                ladentextur(0,"textur//brick30.jpg",true);
                                ladentextur(0,"textur//brick31.jpg",true);
                                ladentextur(0,"textur//brick32.jpg",true);
                                ladentextur(0,"textur//brick33_512.jpg",true);
                                
                                ladentextur(0,"textur//einbahnstrasse.png",true);
                                ladentextur(0,"textur//vorfahrtgewaehren.png",true);
                                ladentextur(0,"textur//verboteinfahrt.png",false);
                                ladentextur(0,"textur//vorfahrt.png",false);
                                ladentextur(0,"textur//vorfahrtvonrechts.png",false);

                                ladentextur(0,"textur//verkehr_einbahnstrasse.jpg",true);
                                ladentextur(0,"textur//verkehr_vorfahrtgewaehren.jpg",true);
                                ladentextur(0,"textur//verkehr_verboteinfahrt.jpg",false);
                                ladentextur(0,"textur//verkehr_vorfahrt.jpg",false);
                                ladentextur(0,"textur//verkehr_vorfahrtvonrechts.jpg",false);

                                ladentextur(0,"textur//metall03.jpg",true);
                                ladentextur(0,"textur//metall04.jpg",true);
                                ladentextur(0,"textur//metall05.jpg",true);


};
void _hauptfenster::ladentextur(unsigned int i,_zeichenkette<char> s,bool clamp){
                                _textur<_tb>*t=texturverwaltung->erzeugentextur(i,s);
                                _bild<_tb>*b=texturverwaltung->erzeugenbild(i,s);
                                t->einfuegenbitmap(b);
                                //bild[i]=new _bildtga<>(s,1,1);
                                //textur[i]->einfuegenbitmap(bild[i]);
                               // b->tiefereskalieren(1);
                               // b->datentausch(0,2);
                                b->wiederholung(0,clamp);
                                b->wiederholung(1,clamp);
};
void _hauptfenster::aktualisieren(){
                                zeichnen();
};
void _hauptfenster::zeichnen(){
                                ansicht[0]->neuzeichnen();
                                ansicht[1]->neuzeichnen();
                                ansicht[2]->neuzeichnen();
                                ansicht[3]->neuzeichnen();
                                texturansicht->neuzeichnen();
};
void _hauptfenster::loeschenanwahl(){
                                //anwahlvertex=0;
                                //anwahlpolygon=0;
                                //anwahlkante[0]=0;
                                //anwahlkante[1]=0;
                                //anwahlnetz=0;
                                anwahllicht=0;
                                anwahlknoten=0;
                                anwahlpartikelquelle=0;
                                anwahlgravitation=0;
                                anwahlfeldelektrostatisch=0;
                                anwahlfeldmagnetostatisch=0;
                                anwahlkugel=0;
                                
								anwahlvertexliste.aushaengen();
								anwahlpolygonliste.aushaengen();
								anwahlkanteliste.aushaengen();
								anwahlnetzliste.aushaengen();
								anwahllichtliste.aushaengen();
								anwahlpartikelquelleliste.aushaengen();
								anwahlgravitationliste.aushaengen();
								anwahlfeldelektrostatischliste.aushaengen();
								anwahlfeldmagnetostatischliste.aushaengen();
								anwahlkugelliste.aushaengen();
								anwahlknotenliste.aushaengen();                                
};

unsigned int _hauptfenster::abfrage(const _zeichenkette<char>&titel,const _zeichenkette<char>&text){
                                bcUInt32 b=MB_YESNO;
                                if(IDYES==nachricht(ANSIToUnicode(text.daten()),ANSIToUnicode(titel.daten()),b)) return(1);
                                /*
                                IDABORT Abort button was selected.  
                                IDCANCEL Cancel button was selected.  
                                IDCONTINUE Continue button was selected.  
                                IDIGNORE Ignore button was selected.  
                                IDNO No button was selected.  
                                IDOK OK button was selected.  
                                IDRETRY Retry button was selected.  
                                IDTRYAGAIN Try Again button was selected.  
                                IDYES Yes button was selected.                                  
                                */
                                return(0);
};
unsigned int _hauptfenster::information(const _zeichenkette<char>&titel,const _zeichenkette<char>&text){
                                bcUInt32 b=MB_OK;
                                nachricht(ANSIToUnicode(text.daten()),ANSIToUnicode(titel.daten()),b);
                                return(0);
};
void _hauptfenster::beinichtdefiniert(_guiereignisdaten *){
                                information("Hinweis","Funktion noch nicht definiert");
};
void _hauptfenster::beischliessen(_guiereignisdaten *){
                                if(corundwelt) delete corundwelt;
                                corundwelt=0;
                                zerstoeren();
};
void _hauptfenster::beizerstoeren(_guiereignisdaten *){
                                PostQuitMessage(0); 
};
void _hauptfenster::beikonversion(_guiereignisdaten*){
                                if(corundwelt){
                                 if(abfrage("Frage","Eine Konversion der Karten erfordet das Schließen der aktuellen Karte. Soll sie geschlossen werden?")){
                                  delete corundwelt;
                                  corundwelt=0;
                                  zeichnen();                               
                                 };
                                };
                                if(abfrage("Frage","Soll die Konversion wirklich durchgefpührt werden ?")){

                                 //konvertieren aller duplikate
                                 _liste<_zeichenkette<char> > liste;
                                 _listenknoten<_zeichenkette<char> >*zit;
                                 _zeichenkette<char>*z;
                                 HANDLE fHandle; 
                                 WIN32_FIND_DATAA wfd; 
                                 fHandle=FindFirstFileA("welt\\_corundkarte*.txt",&wfd); 
                                 z=new _zeichenkette<char>(wfd.cFileName);z->anhaengenfront("welt\\");
                                 liste.einhaengen(z);
                                 while(FindNextFileA(fHandle,&wfd)){ 
                                  if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ 
                                   //Datei ist keine, sondern ein Verzeichnis... 
                                  }else{ 
                                   z=new _zeichenkette<char>(wfd.cFileName);z->anhaengenfront("welt\\");
                                   liste.einhaengen(z);
                                  };
                                 };
                                 FindClose(fHandle);
                                 
                                 if(liste.anfang(zit))do{
                                 
                                  loeschenanwahl();
                                  ansicht[0]->grafik->aktivitaet(true);
                                  corundweltladen(this,zit->objekt(),corundwelt,ansicht[0]->grafik,akustik);
                                  corundwelt->speichername.setzen(zit->objekt());
                                  zeichnen();
                                  texturansicht->aktualisieren();                                
                                  texturansicht->neuzeichnen(); 
                                  statusbar->text(2,L"Welt wurde geladen.");
                                  corundweltspeichern(this,zit->objekt(),corundwelt);
                                  delete corundwelt;
                                  corundwelt=0;
                                  zeichnen();                               
                                  
                                  _zeichenkette<char> h="Folgende Datei wurde konvertiert : ";
                                  h+=*zit->objekt();
                                  statusbar->text(2,ANSIToUnicode(h.daten()));
                                 }while(liste.naechstes(zit));
                                 liste.loeschen();
                                };


                                
};
void _hauptfenster::beieigenschaften(_guiereignisdaten*){
                                //dyndialog->Reset(L"Programmeigenschaften bearbeiten");
                                einhaengendialog(dyndialog);
                                dyndialog->zeigen();
};
//------------------------------ WELT -----------------------------------------------------
void _hauptfenster::beiweltneu(_guiereignisdaten *){
                                if(corundwelt) delete corundwelt;
                                corundwelt=0;
                                ansicht[0]->grafik->aktivitaet(true);
                                corundwelt=new _corundwelt(ansicht[0]->grafik,*texturverwaltung,akustik,*tonverwaltung);
                                loeschenanwahl();
                                ansicht[0]->neuzeichnen();
                                ansicht[1]->neuzeichnen();
                                ansicht[2]->neuzeichnen();
                                ansicht[3]->neuzeichnen();
                                texturansicht->aktualisieren();                                
                                texturansicht->neuzeichnen();                                
                                statusbar->text(2,L"Welt wurde neu angelegt.");
};
void _hauptfenster::beiweltladen(_guiereignisdaten*){
                                _guidialogdatei*m_fileDialog=new _guidialogdatei(this); 
                                m_fileDialog->addierenfilter(L"corundwelt (*.txt)", L"*.txt"); 
                                m_fileDialog->addierenfilter(L"corundwelt (*.bin)", L"*.bin"); 
                                
                                m_fileDialog->standarderweiterung(L"txt");
                                if(m_fileDialog->oeffnen()){
                                 if(corundwelt) delete corundwelt;
                                 corundwelt=0;
                                 loeschenanwahl();
                                 ansicht[0]->grafik->aktivitaet(true);

								 _zeichenkette<char> h=UnicodeToANSI(m_fileDialog->dateiname()).Data();
								 unsigned int si=0;
								 if(h.suchenunsensibel(".bin",si)){
							      corundwelt=new _corundwelt(ansicht[0]->grafik,*texturverwaltung,akustik,*tonverwaltung);
								  weltladenbinaer(h,corundwelt->welt,texturverwaltung);
								 }else{
                                  corundweltladen(this,h,corundwelt,ansicht[0]->grafik,akustik);
								 };
                                 corundwelt->speichername.setzen(UnicodeToANSI(m_fileDialog->dateiname()).Data());


                                 ansicht[0]->neuzeichnen();
                                 ansicht[1]->neuzeichnen();
                                 ansicht[2]->neuzeichnen();
                                 ansicht[3]->neuzeichnen();
                                 texturansicht->aktualisieren();                                
                                 texturansicht->neuzeichnen(); 
                                 statusbar->text(2,L"Welt wurde geladen.");
                                };
                                delete m_fileDialog;
};
void _hauptfenster::beiweltladenhart(_guiereignisdaten*){
                                dhart->zeigen();
                                loeschenanwahl();
};
void _hauptfenster::beiweltimportieren(_guiereignisdaten*){
								if(corundwelt==0) beiweltneu(0);
                                _guidialogdatei*dd=new _guidialogdatei(this); 
                                dd->addierenfilter(L"3d Studio (*.3ds)", L"*.3ds"); 
                                dd->standarderweiterung(L"3ds");
                                if(dd->oeffnen()){

                                 _zeichenkette<char> h=UnicodeToANSI(dd->dateiname()).Data();
                                 _welt3DSLoader*wl=new _welt3DSLoader();
                                 _listenknoten<_welt3DSObject>*oit;
                                 _liste<_welt3DSObject> lo;
                                 _vertex**lv=0;
                                 _verbindervertexpolygon*cit;
                                 wl->Load(h.daten(),&lo);
                                 statusbar->text(2,L"3ds Datei wurde geladen, Netze werden konvertiert.");
                                 //L->l("FUCK");
                                 iterierenliste(&lo,oit,
                                  _welt3DSObject*o=oit->objekt();
                                  _netz*n=new _netz();
                                  n->einhaengen(corundwelt->welt);
                                  unsigned short i;
                                  lv=new _vertex*[o->GetVertexCount()];
                                  
                                  //lv.aushaengen();
                                  for(i=0;i<o->GetVertexCount();i++){
                                   _vektor3<_tg> h(o->GetVertices()[i].x,o->GetVertices()[i].y,o->GetVertices()[i].z);
                                   _vertex*v=new _vertex(n,h);
                                   
                                   lv[i]=v;
                                  }; 
                                  
                                  _vektor2<_tg> b2;
                                  for(i=0;i<o->GetFaceCount();i++){
                                   _polygon*p=new _polygon(n);
                                   _vertex*v0=lv[o->GetFaces()[i].v1];
                                   _vertex*v1=lv[o->GetFaces()[i].v2];
                                   _vertex*v2=lv[o->GetFaces()[i].v3];
                                   //p->vertex(v0);
                                   cit=new _verbindervertexpolygon(v0,p);
                                   if(o->GetTexCoords()){
                                    b2.setzen(o->GetTexCoords()[o->GetFaces()[i].v1].u,o->GetTexCoords()[o->GetFaces()[i].v1].v);
                                    cit->einfuegenbitmapvektor(b2);
                                   };
                                   
                                   cit=new _verbindervertexpolygon(v1,p);
                                   if(o->GetTexCoords()){
                                    b2.setzen(o->GetTexCoords()[o->GetFaces()[i].v2].u,o->GetTexCoords()[o->GetFaces()[i].v2].v);
                                    cit->einfuegenbitmapvektor(b2);
                                   };
                                   
                                   cit=new _verbindervertexpolygon(v2,p);
                                   if(o->GetTexCoords()){
                                    b2.setzen(o->GetTexCoords()[o->GetFaces()[i].v3].u,o->GetTexCoords()[o->GetFaces()[i].v3].v);
                                    cit->einfuegenbitmapvektor(b2);
                                   };
                                   
                                  }; 
                                  
                                  
                                  delete[] lv;
                                  n->aktualisieren();
                                  n->invertieren();
                                  n->verknuepfenverbindervertexpolygon();
                                  
                                  L->l("Ein 3ds Netz wurde geladen.");
                                 );
                                 L->l("Die Welt besitzt nach dem Laden polygonanzahl =",(int)corundwelt->welt->anzahlpolygon());
                                 lo.loeschen();
                                 delete wl;
                                 
                                 
                                 ansicht[0]->neuzeichnen();
                                 ansicht[1]->neuzeichnen();
                                 ansicht[2]->neuzeichnen();
                                 ansicht[3]->neuzeichnen();
                                 texturansicht->aktualisieren();                                
                                 texturansicht->neuzeichnen(); 
                                 statusbar->text(2,L"3ds Datei wurde importiert.");
								};								
								delete dd;
								
};
void _hauptfenster::beiweltspeichern(_guiereignisdaten*){
                                if(corundwelt){
                                 _guidialogdatei*m_fileDialog = new _guidialogdatei(this); 
                                 m_fileDialog->addierenfilter(L"corundwelt (*.txt)", L"*.txt"); 
                                 m_fileDialog->addierenfilter(L"corundwelt (*.bin)", L"*.bin"); 
                                 m_fileDialog->standarderweiterung(L"txt");
                                 if(m_fileDialog->speichern()){
                                  corundwelt->speichername=UnicodeToANSI(m_fileDialog->dateiname()).Data();
								  unsigned int si=0;
								  if(corundwelt->speichername.suchenunsensibel(".bin",si)){
								  
								   
                                   weltspeichernbinaer(corundwelt->speichername,corundwelt->welt);
								  }else{
								   corundweltspeichern(this,corundwelt->speichername,corundwelt);
								  };
                                  statusbar->text(2,L"Welt wurde gespeichert");
                                 };
                                 delete m_fileDialog;
                                }else information("Hinweis","Es liegt keine Welt vor.");
};

void _hauptfenster::beiweltschliessen(_guiereignisdaten *){
                                if(corundwelt) delete corundwelt;
                                corundwelt=0;
                                zeichnen();                               
};
void _hauptfenster::beiweltkomplanarenichtzeichnen(_guiereignisdaten*){
                                if(corundwelt){
                                 _welt*w=corundwelt->welt;
                                 _netz*n;
                                 if(w->anfang(n))do{
                                  netzkomplanarenichtzeichnen(n);
                                 }while(w->naechstes(n));
                                };
};
void _hauptfenster::beiweltkomplanarenichtkollidieren(_guiereignisdaten*){
                                if(corundwelt){
                                 _welt*w=corundwelt->welt;
                                 _netz*n;
                                 if(w->anfang(n))do{
                                  netzkomplanarenichtkollidieren(n);
                                 }while(w->naechstes(n));
                                };
};
void _hauptfenster::beiweltkomplanarekeinschattenwurflightmap(_guiereignisdaten*){
                                if(corundwelt){
                                 _welt*w=corundwelt->welt;
                                 _netz*n;
                                 if(w->anfang(n))do{
                                  netzkomplanarekeinschattenwurflightmap(n);
                                 }while(w->naechstes(n));
                                };
};
void _hauptfenster::netzkomplanarenichtzeichnen(_netz*n){
                                _polygon*pit;
                                _polygon*p;
                                _netz*nit;
                                _welt*w=corundwelt->welt;
                                if(n->anfang(p))do{
                                 if(w->anfang(nit))do{
                                  if(nit!=n){
                                   if(nit->anfang(pit))do{
                                    if(p->abgedeckt(pit)){
                                     p->zeichnenflaeche(false);
                                    };
                                   }while(nit->naechstes(pit));
                                  };
                                 }while(w->naechstes(nit));
                                }while(n->naechstes(p));
                                
};
void _hauptfenster::netzkomplanarenichtkollidieren(_netz*n){
                                _polygon*pit;
                                _polygon*p;
                                _netz*nit;
                                _welt*w=corundwelt->welt;
                                if(n->anfang(p))do{
                                 if(w->anfang(nit))do{
                                  if(nit!=n){
                                   if(nit->anfang(pit))do{
                                    if(p->abgedeckt(pit)){
                                     p->kollision(false);
                                    };
                                   }while(nit->naechstes(pit));
                                  };
                                 }while(w->naechstes(nit));
                                }while(n->naechstes(p));
                                
};
void _hauptfenster::netzkomplanarekeinschattenwurflightmap(_netz*n){
                                _polygon*pit;
                                _polygon*p;
                                _netz*nit;
                                _welt*w=corundwelt->welt;
                                if(n->anfang(p))do{
                                 if(w->anfang(nit))do{
                                  if(nit!=n){
                                   if(nit->anfang(pit))do{
                                    if(p->abgedeckt(pit)){
                                     p->lightmapschattierung(false);
                                    };
                                   }while(nit->naechstes(pit));
                                  };
                                 }while(w->naechstes(nit));
                                }while(n->naechstes(p));
                                
};
void _hauptfenster::beiwelteigenschaften(_guiereignisdaten*){
                                if(corundwelt){
                                 dyndialog->neusetzen(L"Welteigenschaften bearbeiten");
                                 corundwelt->einhaengendialog(dyndialog);
                                 dyndialog->zeigen();
                                };
};
void _hauptfenster::beiweltzonenvorerstellen(_guiereignisdaten*){
                                if(corundwelt){
                                 statusbar->text(2,L"Zonen werden erstellt. Bitte warten...");
                                 _liste<_netz>*rohnetze;
                                 rohnetze=corundwelt->welt->uebersetzen();
                                 //_listenknoten<_netz>*nit;
                                 //if(rohnetze->anfang(nit))do{
                                 // nit->objekt()->einhaengen(corundwelt->welt);
                                 //}while(rohnetze->naechstes(nit));
                                 rohnetze->loeschen();
                                 delete rohnetze;
                                 corundwelt->welt->unuebersetzen();
                                 zeichnen();
                                 statusbar->text(2,L"Zonen wurden erstellt, gelöscht. Intersektionsergebnis liegt wor. Rohdaten gelöscht.");
                                }else information("Hinweis","Keine Welt vorhanden.");
};
void _hauptfenster::beiweltzonenerstellen(_guiereignisdaten*){
                                if(corundwelt){
                                 statusbar->text(2,L"Zonen werden erstellt. Bitte warten...");
                                 _liste<_netz>*rohnetze;
                                 rohnetze=corundwelt->welt->uebersetzen();
                                 _listenknoten<_netz>*nit;
                                 if(rohnetze->anfang(nit))do{
                                  nit->objekt()->einhaengen(corundwelt->welt);
                                 }while(rohnetze->naechstes(nit));
                                 rohnetze->aushaengen();
                                 delete rohnetze;
                                 zeichnen();
                                 statusbar->text(2,L"Zonen wurden erstellt.");
                                }else information("Hinweis","Keine Welt vorhanden.");
};
void _hauptfenster::beiweltzonenloeschen(_guiereignisdaten*){
                                if(corundwelt){
                                 _partition::_zone*zit;
                                 if(corundwelt->welt->anfang(zit)){
                                  corundwelt->welt->unuebersetzen();
                                  zeichnen();
                                  statusbar->text(2,L"Zonen wurden gelöscht.");
                                 }else information("Fehler","Die Welt enthält bereits keine Zonen.");
                                }else information("Fehler","Keine Welt vorhanden.");
};
void _hauptfenster::beiweltzonenbestrahlen(_guiereignisdaten*){
};
void _hauptfenster::beiwelttestenohnebestrahlung(_guiereignisdaten*){
                                testenwelt(false,false);
};
void _hauptfenster::beiwelttesten(_guiereignisdaten*){
                                testenwelt(true,false);
};
void _hauptfenster::beiwelttestenspinnmania(_guiereignisdaten*){
                                if(corundwelt){
                                 testmodus=true;
                                 _welt*w=corundwelt->welt;
                                 _netz*nit;
                                 _partition::_zone*zit;
                                 //_zeichenkette<char> altname;
                                 double sp0,sp1;
                                 if(w->anfang(nit)){
                                  statusbar->text(2,L"Die Welt wird zwischengespeichert. Bitte warten ...");
                                  corundweltspeichern(this,"welt\\temp.txt",corundwelt);
                                  sp0=splittervertikal[0]->lesen();
                                  sp1=splitterhorizontal->lesen();
                                  splittervertikal[0]->setzen(1);
                                  splitterhorizontal->setzen(1);

                                //hauptfunktion zum testen einzelner szenen ohne verbund
                                _welt*w=corundwelt->welt;
                                _netz*nit;
                                _partition::_zone*zit;
                                _liste<_netz>*rohnetze;
                                //--------------------
                                testenweltanlegenlightmap(true);
                                testenweltuebersetzen(rohnetze);
                                zeichnen();
                                ansicht[0]->grafik->aktivitaet(true);
                                //rohnetze isoliert behalten und zonen bestrahlen
                                if(w->anfang(zit)){
                                 corundwelt->mo->verstecken();
                                 testenweltbestrahlen(zit,true);
                                 //nun testen
                                 _grafik*grafik=ansicht[0]->grafik;
                                 _kamera<_tg>*kamera=ansicht[3]->kamera;
                                 _win::_system*ss=new _win::_system(0);
                                 corundwelt->initialisierenanimation(grafik);
                                 while((corundwelt->kb->escape()==false)) {
                                  _matrix44<float> mw;
                                  _matrix44<float> mm;
                                  _matrix44<float> mp;
                                  mw.setzenidentitaet();
                                  mm.setzenidentitaet();
                                  mp.setzenidentitaet();
                                  kamera->ladenmatrix<float>(&mm,&mp,80,80);
                                  grafik->matrixwelt(&mw); 
                                  grafik->matrixprojektion(&mp);
                                  grafik->matrixmodell(&mm);
                                  _partition::_sektor*sektor=0;
                                  _partition::_zone*zone=0;
                                  if(w->anfang(zone)){
                                   sektor=zone->sektor(*kamera);
                                   if(sektor){
                                    sektor->visualisieren();
                                    sektor->zeichnen(grafik,kamera);
                                   };
                                  };
                                  if(sektor==0){
                                   _netz*nit;
                                   if(w->anfang(nit)){
                                    nit->zeichnendebug(grafik);
                                   };
                                  };
                                  //if(inventar) inventar->zeichnen(grafik);
                                  grafik->tiefenbufferkondition(false);
                                  ss->animieren();
                                 };
                                 corundwelt->deinitialisierenanimation();
                                 for(int u=0;u<4;u++) {ansicht[u]->grafik->aktivitaet(true); ansicht[u]->grafik->nebel(false);};
                                 delete ss;
                                 corundwelt->mo->zeigen();
                                 ansicht[0]->grafik->aktivitaet(true);
                                }else information("Fehler","Die Welt besitzt nach dem Kompilieren keine Zone, obwohl Netze vorhanden waren.");
                                //die welt uncompilieren, zonennetze vorher löschen und die rohnetz wieder in die welt einhaengen
                                testenweltloeschenlightmap();
                                testenweltunuebersetzen(rohnetze);

                                  splittervertikal[0]->setzen(sp0);
                                  splitterhorizontal->setzen(sp1);
                                  zeichnen();
                                  loeschenanwahl();
                                  if(corundwelt) delete corundwelt;
                                  corundwelt=0;
                                  ansicht[0]->grafik->aktivitaet(true);
                                  corundweltladen(this,"welt\\temp.txt",corundwelt,ansicht[0]->grafik,akustik);
                                  //corundwelt->speichername=altname;
                                  zeichnen();
                                  texturansicht->aktualisieren();
                                  texturansicht->neuzeichnen(); 
                                  statusbar->text(2,L"Welt wurde rückgeladen.");
                                 }else information("Fehler","Die Welt besitzt kein Netz.");
                                 testmodus=false;
                                }else information("Fehler","Keine Welt vorhanden zum Testen.");};

void _hauptfenster::beiwelttestenverbund(_guiereignisdaten*){
                                                               
                               if(corundwelt){
                                if(abfrage("Achtung","Das Testen des Weltverbundes bedingt eine Speicherung der aktuellen Karte und die Löschung aller temporärer Welten. Soll wirklich gespeichert werden ?")){
                                 testmodus=true;
                                 corundwelt->mo->verstecken();



                                 //löschen aller duplikate
                                 _liste<_zeichenkette<char> > liste;
                                 _listenknoten<_zeichenkette<char> >*zit;
                                 _zeichenkette<char>*z;
                                 HANDLE fHandle; 
                                 WIN32_FIND_DATAA wfd; 
                                 fHandle=FindFirstFileA("welt\\*.mow",&wfd); 
                                 z=new _zeichenkette<char>(wfd.cFileName);z->anhaengenfront("welt\\");
                                 liste.einhaengen(z);
                                 while(FindNextFileA(fHandle,&wfd)){ 
                                  if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ 
                                   //Datei ist keine, sondern ein Verzeichnis... 
                                  }else{ 
                                   z=new _zeichenkette<char>(wfd.cFileName);z->anhaengenfront("welt\\");
                                   liste.einhaengen(z);
                                  };
                                 };
                                 FindClose(fHandle);
                                 if(liste.anfang(zit))do{
                                  remove(zit->objekt()->daten());
                                  _zeichenkette<char> h="Folgende Datei wurde gelöscht : ";
                                  h+=*zit->objekt();
                                  statusbar->text(2,ANSIToUnicode(h.daten()));
                                 }while(liste.naechstes(zit));
                                 liste.loeschen();

                                 //die momentan geladene welt abspeichern als tmp und test starten
                                 //---------------------------------------------------------------------------
                                 _netz*nit;
                                 _partition::_zone*zone;
                                 _liste<_netz>*rohnetze;
                                 double sp0,sp1;
                                 if(corundwelt->welt->anfang(nit)==false){
                                  statusbar->text(2,L"Keine Netze in der Welt vorhanden.");
                                  corundwelt->mo->zeigen();
                                  testmodus=false;
                                  return;
                                 };
                                 statusbar->text(2,L"Die Welt wird zwischengespeichert. Bitte warten ...");
                                 corundweltspeichern(this,"welt\\temp.txt",corundwelt);
                                 sp0=splittervertikal[0]->lesen();
                                 sp1=splitterhorizontal->lesen();
                                 splittervertikal[0]->setzen(1);
                                 splitterhorizontal->setzen(1);                                 
                                 
                                 
                                //test starten
                                // testenweltverbund();
                                bool stop=false;
                                do{
                    
                                 testenweltanlegenlightmap(true);
                                 testenweltuebersetzen(rohnetze);
                                 //zeichnen();
                                 ansicht[0]->grafik->aktivitaet(true);
                                 //rohnetze isoliert behalten und zonen bestrahlen
                                 if(corundwelt->welt->anfang(zone)){
                                  testenweltbestrahlen(zone,true);
                                  //nun testen
                                  _grafik*gra=ansicht[0]->grafik;
                                  _win::_system*ss=new _win::_system(0);
                                  corundwelt->initialisierenanimation(gra);
                                  while((corundwelt->kb->escape()==false)&&(corundwelt->naechstekarte==-1)) {
                                   corundwelt->animieren(gra,akustik);
                                   ss->animieren();
                                  };
                                  corundwelt->deinitialisierenanimation();
                                  if(corundwelt->naechstekarte==-1) stop=true;
                                  

                                  
                                  
                                  
                                  
                                  delete ss;
                                  //corundwelt->mo->zeigen();
                                  ansicht[0]->grafik->aktivitaet(true);
                                 }else information("Fehler","Die Welt besitzt nach dem Kompilieren keine Zone, obwohl Netze vorhanden waren.");
                                 //die welt uncompilieren, zonennetze vorher löschen und die rohnetz wieder in die welt einhaengen
                                 testenweltloeschenlightmap();
                                 testenweltunuebersetzen(rohnetze);
                                 for(int u=0;u<4;u++) {ansicht[u]->grafik->aktivitaet(true); ansicht[u]->grafik->nebel(false);};
                                
                                
                                  if(!stop){
                                   //diese welt speichern
                                   _zeichenkette<char> mow=corundwelt->speichername;
                                   mow.ersetzen(".txt",".mow");
                                   corundweltspeichern(this,mow,corundwelt);
                                   corundwelt->speichername=mow;
                                  };                                 
                                 
                                 
                                 
                                 if(!stop){
                                  //naechste karte laden
                                  
                                  //kartenindex bestimmen
                                  _zeichenkette<char> h;
                                  _zeichenkette<char> datei;
                                  unsigned int knoten=corundwelt->naechsterknoten;
                                  _corundknoten*knit;
                                  char buf[128];
                                  _itoa(corundwelt->naechstekarte,buf,10);
                                  h=buf;
                                  L->schreiben("Datei wird gel");
                                  while(h.groesse()!=3) h.anhaengenfront("0");
                                  h.anhaengenfront("welt\\_corundkarte");
                                  L->schreiben("Datei wird gelsdgsdfg");
                                  if(corundwelt) delete corundwelt;
                                  corundwelt=0;                                  
                                  //1. versuch : mow laden
                                  datei=h;
                                  datei+=".mow";
                                  L->schreiben("Datei wird gelesen :",datei);
                                  if(dateiexistiert(datei)) corundweltladen(this,datei,corundwelt,ansicht[0]->grafik,akustik); else{
                                   //2. versuch : txt laden
                                   datei=h;
                                   datei+=".txt";
                                   L->schreiben("Datei wird gelesen :",datei);
                                   if(dateiexistiert(datei)) corundweltladen(this,datei,corundwelt,ansicht[0]->grafik,akustik); else stop=true;
                                  };
                                  if(!stop){
                                   if(corundwelt->spieler){
                                    if(corundwelt->anfang(knit))do{
                                     if(knoten==knit->index) {
                                      corundwelt->spieler->_kollidierbarkugel::ort(knit->ort);
                                      corundwelt->spieler->_kugel::ort(knit->ort);
                                     };
                                    }while(corundwelt->naechstes(knit));
                                   };
                                  };
                                 };
                                
                                }while(!stop);

                                 
                                
                                
                                
                                
                                
                                
                                
                                  splittervertikal[0]->setzen(sp0);
                                  splitterhorizontal->setzen(sp1);
                                  zeichnen();                                
                                  loeschenanwahl();
                                  if(corundwelt) delete corundwelt;
                                  corundwelt=0;
                                  ansicht[0]->grafik->aktivitaet(true);         
                                  corundweltladen(this,"welt\\temp.txt",corundwelt,ansicht[0]->grafik,akustik);
                                  //corundwelt->speichername=altname;
                                  zeichnen();
                                  texturansicht->aktualisieren();                                
                                  texturansicht->neuzeichnen(); 
                                  statusbar->text(2,L"Welt wurde rückgeladen.");    
                                  corundwelt->mo->zeigen();                                                       
                                  testmodus=false;
                                
                                
                                
                                };
                                //corundwelt->mo->zeigen();  
                               }else information("Fehler","Keine Welt vorhanden.");
                               
};                                
void _hauptfenster::testenwelt(bool lightmaps,bool verbund){
                                if(corundwelt){
                                 testmodus=true;
                                 _welt*w=corundwelt->welt;
                                 _netz*nit;
                                 _partition::_zone*zit;
                                 //_zeichenkette<char> altname;
                                 double sp0,sp1;
                                 if(w->anfang(nit)){
                                  statusbar->text(2,L"Die Welt wird zwischengespeichert. Bitte warten ...");
                                  corundweltspeichern(this,"welt\\temp.txt",corundwelt);
                                  sp0=splittervertikal[0]->lesen();
                                  sp1=splitterhorizontal->lesen();
                                  splittervertikal[0]->setzen(1);
                                  splitterhorizontal->setzen(1);
                                  testenwelteinzel(lightmaps);
                                  splittervertikal[0]->setzen(sp0);
                                  splitterhorizontal->setzen(sp1);
                                  zeichnen();
                                  loeschenanwahl();
                                  if(corundwelt) delete corundwelt;
                                  corundwelt=0;
                                  ansicht[0]->grafik->aktivitaet(true);
                                  corundweltladen(this,"welt\\temp.txt",corundwelt,ansicht[0]->grafik,akustik);
                                  //corundwelt->speichername=altname;
                                  zeichnen();
                                  texturansicht->aktualisieren();
                                  texturansicht->neuzeichnen(); 
                                  statusbar->text(2,L"Welt wurde rückgeladen.");
                                 }else information("Fehler","Die Welt besitzt kein Netz.");
                                 testmodus=false;
                                }else information("Fehler","Keine Welt vorhanden zum Testen.");
};
void _hauptfenster::testenwelteinzel(bool lightmaps){                                  
                                //hauptfunktion zum testen einzelner szenen ohne verbund
                                _welt*w=corundwelt->welt;
                                _netz*nit;
                                _partition::_zone*zit;
                                _liste<_netz>*rohnetze;
                                //--------------------
                                testenweltanlegenlightmap(lightmaps);
                                testenweltuebersetzen(rohnetze);
                                zeichnen();
                                ansicht[0]->grafik->aktivitaet(true);
                                //rohnetze isoliert behalten und zonen bestrahlen
                                if(corundwelt->welt->anfang(zit)){
                                 corundwelt->mo->verstecken();
                                 testenweltbestrahlen(zit,lightmaps);
                                 //nun testen
                                 _grafik*gra=ansicht[0]->grafik;
                                 _win::_system*ss=new _win::_system(0);
                                 corundwelt->initialisierenanimation(gra);
                                 while((corundwelt->kb->escape()==false)&&(corundwelt->naechstekarte==-1)) {
                                  corundwelt->animieren(gra,akustik);
                                  ss->animieren();
                                  
                                 };
                                 corundwelt->deinitialisierenanimation();
                                 for(int u=0;u<4;u++) {ansicht[u]->grafik->aktivitaet(true); ansicht[u]->grafik->nebel(false);};
                                 delete ss;
                                 corundwelt->mo->zeigen();
                                 ansicht[0]->grafik->aktivitaet(true);
                                }else information("Fehler","Die Welt besitzt nach dem Kompilieren keine Zone, obwohl Netze vorhanden waren.");
                                //die welt uncompilieren, zonennetze vorher löschen und die rohnetz wieder in die welt einhaengen
                                testenweltloeschenlightmap();
                                testenweltunuebersetzen(rohnetze);
};                                  


void _hauptfenster::testenweltanlegenlightmap(bool lightmaps){
                                if(lightmaps){
                                 char j[1024];
                                 unsigned int i=0,e;
                                 bool l;
                                 _zeichenkette<char> h=corundwelt->speichername;
                                 _zeichenkette<char> lm="lightmap//";
                                 if(h.suchen(".",i)){
                                  h.aushaengen(i,h.groesse()-i);
                                 };
                                 i=0;
                                 l=false;
                                 e=0;
                                 while(h.suchen("\\",i)){
                                  e=i;
                                  i++;
                                  l=true;
                                 };
                                 if(l) h.aushaengen(0,e+1);
                                 i=0;
                                 l=false;
                                 e=0;
                                 while(h.suchen("/",i)){
                                  e=i;
                                  i++;
                                  l=true;
                                 };
                                 if(l) h.aushaengen(0,e+1);
                                 corundwelt->welt->anlegenlightmap(&corundwelt->textur,lm+h+"_");
                                };
};
void _hauptfenster::testenweltuebersetzen(_liste<_netz>*&rohnetze){                                  
                                _netz*nit;
                                _partition::_zone*zit;
                                //--------------------
                                if(corundwelt->welt->anfang(zit)){
                                 if(abfrage("Frage","Die Welt besitzt noch alte Zonen. Sollen die Zonennetze wieder der Welt zugeordnet werden ? (wenn nein, dann wird gelöscht)")){
                                  corundwelt->welt->unuebersetzen();
                                 }else{
                                  if(corundwelt->welt->anfang(nit))do{
                                   if(nit->zonennetz()) nit->_listenknotenbasis<_netz>::loeschmarkierung(true);
                                  }while(corundwelt->welt->naechstes(nit));
                                  corundwelt->welt->_listebasis<_netz>::loeschenmarkiert();
                                  corundwelt->welt->unuebersetzen();
                                 };
                                };
                                  
                                statusbar->text(2,L"Die Welt wird übersetzt. Bitte warten ...");
                                _win::_system*ws=new _win::_system(0);
                                corundwelt->welt->debugsystem(ws);
                                corundwelt->welt->debuggenintersektion(debugintersektion);
                                corundwelt->welt->debuggensektor(debugsektor);
                                corundwelt->welt->debuggenbsp(debugbsp);
                                corundwelt->welt->debuggenportal(debugportal);
                                corundwelt->welt->debuggensichtbarkeit(debugsichtbarkeit);
                                rohnetze=corundwelt->welt->uebersetzen();
                                corundwelt->welt->debugsystem(0);
                                corundwelt->welt->anfang(nit);
                                nit->farbeverbinder(corundwelt->ambientlicht);
                                delete ws;
};                                  
void _hauptfenster::testenweltbestrahlen(_partition::_zone*zit,bool lightmaps){                                   
                                _vektor3<_to> al(corundwelt->ambientlicht[0],corundwelt->ambientlicht[1],corundwelt->ambientlicht[2]);
                                zit->ambientlicht(al);
                                if(lightmaps){
                                 statusbar->text(2,L"Die Welt wird bestrahlt. Bitte warten ...");
                                 zit->erzeugenvertexlicht();
                                 corundwelt->B->lichtambient(_vektor3<_to>(corundwelt->ambientlicht[0],corundwelt->ambientlicht[1],corundwelt->ambientlicht[2]));
                                 corundwelt->B->bestrahlenlightmapzone(corundwelt->welt);
                                 corundwelt->welt->uebergebenlightmap(ansicht[0]->grafik);
                                 statusbar->text(2,L"Bestrahlung beendet.");
                                }else{
                                 statusbar->text(2,L"Das Vertexlicht wird berechnet. Bitte warten ...");
                                 if(corundwelt->welt->anfang(zit))do{
                                  zit->erzeugenvertexlicht();
                                 }while(corundwelt->welt->naechstes(zit));
                                 statusbar->text(2,L"Das Vertexlichtberechnung beendet.");
                                 //w->uebergebenlightmap(ansicht[0]->grafik);
                                };
};                                   
void _hauptfenster::testenweltloeschenlightmap(){
                                _textur<_tb>*tit;
                                //----------------
                                if(corundwelt->textur.anfang(tit))do{
                                 if(tit->bitmap()->anzahl()==0){
                                  if(tit->lightmap()->anzahl()>0){
                                   tit->loeschen();
                                   tit->_listenknotenbasis<_textur<_tb> >::loeschmarkierung(true);
                                  };
                                 };    
                                }while(corundwelt->textur.naechstes(tit));
                                corundwelt->textur._listebasis<_textur<_tb> >::loeschenmarkiert();
                                _netz*nit;
                                _polygon*pit;
                                if(corundwelt->welt->anfang(nit))do{
                                 if(nit->anfang(pit))do{
                                  pit->texturdynamisch(0);
                                 }while(nit->naechstes(pit));
                                }while(corundwelt->welt->naechstes(nit));
};
void _hauptfenster::testenweltunuebersetzen(_liste<_netz>*rohnetze){                                  
                                _netz*nit;
                                _listenknoten<_netz> *lnnit;
                                //---------------------------
                                if(corundwelt->welt->anfang(nit))do{
                                 if(nit->zonennetz()) {
								  nit->_listenknotenbasis<_netz>::loeschmarkierung(true);
                                 };
                                }while(corundwelt->welt->naechstes(nit));
                                corundwelt->welt->_listebasis<_netz>::loeschenmarkiert();
                                corundwelt->welt->unuebersetzen();
                                if(rohnetze->anfang(lnnit))do{
                                 lnnit->objekt()->einhaengen(corundwelt->welt);
                                }while(rohnetze->naechstes(lnnit));
                                delete rohnetze;
};                  
//------------------------------ UMGEBUNG----------------------------------------------------
void _hauptfenster::beiumgebungschwarz(_guiereignisdaten*){
                                if(corundwelt){
                                 for(int i=0;i<6;i++) dumgebung->textur[i]=corundwelt->textur[3];
                                 dumgebung->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Umgebung anlegen können.");
};
void _hauptfenster::beiumgebungbergpanoramaheiter(_guiereignisdaten*){
                                if(corundwelt){
                                 dumgebung->textur[0]=corundwelt->textur[18];
                                 dumgebung->textur[1]=corundwelt->textur[18];
                                 dumgebung->textur[2]=corundwelt->textur[19];
                                 dumgebung->textur[3]=corundwelt->textur[20];
                                 dumgebung->textur[4]=corundwelt->textur[21];
                                 dumgebung->textur[5]=corundwelt->textur[22];                                 
                                 dumgebung->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Umgebung anlegen können.");
};
//------------------------------ NETZ ----------------------------------------------------
void _hauptfenster::beinetznetz(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gnetz->standardtextur(texturansicht->anwahl());
                                gnetz->einhaengendialog(dnetz);
                                dnetz->zeigen();
};
void _hauptfenster::beinetzscheibe(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gscheibe->standardtextur(texturansicht->anwahl());
                                gscheibe->einhaengendialog(dscheibe);
                                dscheibe->zeigen();
};
void _hauptfenster::beinetzquader(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gquader->standardtextur(texturansicht->anwahl());
                                gquader->einhaengendialog(dquader);
                                dquader->zeigen();
};
void _hauptfenster::beinetzkreuzbalken(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gkreuzbalken->standardtextur(texturansicht->anwahl());
                                gkreuzbalken->einhaengendialog(dkreuzbalken);
                                dkreuzbalken->zeigen();
};
void _hauptfenster::beinetzzylinder(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gzylinder->standardtextur(texturansicht->anwahl());
                                gzylinder->einhaengendialog(dzylinder);
                                dzylinder->zeigen();
};
void _hauptfenster::beinetzkonus(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gkonus->standardtextur(texturansicht->anwahl());
                                gkonus->einhaengendialog(dkonus);
                                dkonus->zeigen();
};
void _hauptfenster::beinetzkugel(_guiereignisdaten *){
                                if(!corundwelt) beiweltneu(0);
                                gkugel->standardtextur(texturansicht->anwahl());
                                gkugel->einhaengendialog(dgkugel);
                                dgkugel->zeigen();
};
void _hauptfenster::beinetztorus(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gtorus->standardtextur(texturansicht->anwahl());
                                gtorus->einhaengendialog(dtorus);
                                dtorus->zeigen();
};
void _hauptfenster::beinetzflaechehermite(_guiereignisdaten *){
								if(!corundwelt) beiweltneu(0);
                                gflaechehermite->standardtextur(texturansicht->anwahl());
                                gflaechehermite->einhaengendialog(dflaechehermite);
                                dflaechehermite->zeigen();
};
//------------------------------ LICHT ----------------------------------------------------
void _hauptfenster::beilichtlicht(_guiereignisdaten *){
                                if(corundwelt){
                                 dlicht->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie ein Licht anlegen können.");
};
//------------------------------ KNOTEN ----------------------------------------------------
void _hauptfenster::beiknotenknoten(_guiereignisdaten *){
                                if(corundwelt){
                                 dknoten->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie einen Knoten anlegen können.");
};
//------------------------------ STEIN  ---------------------------------------------------
template<class OS> OS* _hauptfenster::erzeugencorundstein(OS*schablone){
                               // dstein
                                OS*os=0;
                               /* if(corundwelt){
                                 bool anwahlnutzen=false;
                                 if(anwahlnetz){
                                  if(abfrage("Konstrutkion von Steinen","Sie haben ein Netz angewählt. Soll dieses Netz dupliziert werden, um daraus einen Stein zu konstruieren?")){
                                   anwahlnutzen=true;
                                  };
                                 };
                                 if(anwahlnutzen){                                 
                                  //leeren Stein erzeugen und Zuweisung durchführen
                                  os=new OS(corundwelt);
                                  _netz*n=anwahlnetz->duplizieren();
                                  os->_netz::subtraktiv(n->subtraktiv());
                                  os->_netz::keinbsp(n->keinbsp());
                                  os->_netz::schattenvolumen(n->schattenvolumen());
                                  os->_netz::schattenvolumenlaenge(n->schattenvolumenlaenge());
                                  os->_netz::brechzahl(n->brechzahl());
                                  os->_netz::dispersionsskalierung(n->dispersionsskalierung());
                                  os->_netz::vereinigen(n);
                                  os->_netz::einhaengen(corundwelt->welt);
                                  zeichnen();
                                 }else{
                                  os=new OS(corundwelt);
                                  dstein->netz(os);
                                  dstein->zeigen();
                                 };
                                }else{
                                 information("Hinweis","Sie müssen erst eine Welt erzeugen, bevor Sie einen Stein konstruieren können.");
                                };*/
                                return(os);
};
void _hauptfenster::beisteinnormal(_guiereignisdaten*)   {dsteinnormal->aktivieren();};
void _hauptfenster::beisteincorund(_guiereignisdaten*)   {dsteincorund->aktivieren();};
void _hauptfenster::beisteingummiband(_guiereignisdaten*){dsteingummiband->aktivieren();};
void _hauptfenster::beisteinschere(_guiereignisdaten*)   {dsteinschere->aktivieren();};
void _hauptfenster::beisteinschieb(_guiereignisdaten*)   {dsteinschieb->aktivieren();};
void _hauptfenster::beisteinboulder(_guiereignisdaten*)  {dsteinboulder->aktivieren();};
void _hauptfenster::beisteinrotation(_guiereignisdaten*) {dsteinrotation->aktivieren();};
void _hauptfenster::beisteinimpuls(_guiereignisdaten*)   {dsteinimpuls->aktivieren();};
void _hauptfenster::beisteinelektrisch(_guiereignisdaten*){dsteinelektrisch->aktivieren();};
void _hauptfenster::beisteinerdung(_guiereignisdaten*)   {dsteinerdung->aktivieren();};
void _hauptfenster::beisteinbeschleunigung(_guiereignisdaten*){dsteinbeschleunigung->aktivieren();};
void _hauptfenster::beisteintotenkopf(_guiereignisdaten*){dsteintotenkopf->aktivieren();};
void _hauptfenster::beisteintor(_guiereignisdaten*)      {dsteintor->aktivieren();};
void _hauptfenster::beisteinschalter(_guiereignisdaten*) {dsteinschalter->aktivieren();};
void _hauptfenster::beisteinkugelgen(_guiereignisdaten*) {dsteinkugelgen->aktivieren();};
void _hauptfenster::beisteindach(_guiereignisdaten*)     {dsteindach->aktivieren();};
void _hauptfenster::beisteinflak(_guiereignisdaten*)     {dsteinflak->aktivieren();};
void _hauptfenster::beisteinausgang(_guiereignisdaten*)  {dsteinausgang->aktivieren();};
void _hauptfenster::beisteinsenker(_guiereignisdaten*)   {dsteinsenker->aktivieren();};
void _hauptfenster::beisteinlaser(_guiereignisdaten*)    {dsteinlaser->aktivieren();};
void _hauptfenster::beisteinspiegel(_guiereignisdaten*)  {dsteinspiegel->aktivieren();};
void _hauptfenster::beisteinschloss(_guiereignisdaten*) {dsteinschloss->aktivieren();};
void _hauptfenster::beisteinereignis(_guiereignisdaten*) {dsteinereignis->aktivieren();};
void _hauptfenster::beisteingerissen(_guiereignisdaten*) {dsteingerissen->aktivieren();};
void _hauptfenster::beisteinspuck(_guiereignisdaten*) {dsteinspuck->aktivieren();};
void _hauptfenster::beisteintauscher(_guiereignisdaten*) {dsteintauscher->aktivieren();};
void _hauptfenster::beisteinmagnetisch(_guiereignisdaten*) {dsteinmagnetisch->aktivieren();};
void _hauptfenster::beisteindieb(_guiereignisdaten*) {dsteindieb->aktivieren();};
void _hauptfenster::beisteinfliegengen(_guiereignisdaten*) {dsteinfliegengen->aktivieren();};
void _hauptfenster::beisteinspinnengen(_guiereignisdaten*) {dsteinspinnengen->aktivieren();};
void _hauptfenster::beisteinshogun(_guiereignisdaten*) {dsteinshogun->aktivieren();};
void _hauptfenster::beisteinpuzzle(_guiereignisdaten*) {dsteinpuzzle->aktivieren();};
void _hauptfenster::beisteingas(_guiereignisdaten*) {dsteingas->aktivieren();};
void _hauptfenster::beisteinkombinationsschloss(_guiereignisdaten*) {dsteinkombinationsschloss->aktivieren();};
void _hauptfenster::beisteindrehkreuz(_guiereignisdaten*) {dsteindrehkreuz->aktivieren();};                
void _hauptfenster::beisteineinbahn(_guiereignisdaten*) {dsteineinbahn->aktivieren();};                

void _hauptfenster::beiobjektersatz(_guiereignisdaten*)  {dobjektersatz->aktivieren();};
void _hauptfenster::beiobjektschluessela(_guiereignisdaten*){dobjektschluessela->aktivieren();};
void _hauptfenster::beiobjektbombe(_guiereignisdaten*)   {dobjektbombe->aktivieren();};
void _hauptfenster::beiobjektdynamit(_guiereignisdaten*)   {dobjektdynamit->aktivieren();};
void _hauptfenster::beiobjektmine(_guiereignisdaten*)   {dobjektmine->aktivieren();};
void _hauptfenster::beiobjektsteinpille(_guiereignisdaten*) {dobjektsteinpille->aktivieren();};
void _hauptfenster::beiobjektalkohol(_guiereignisdaten*) {dobjektalkohol->aktivieren();};
void _hauptfenster::beiobjektbungeeseil(_guiereignisdaten*) {dobjektbungeeseil->aktivieren();};
void _hauptfenster::beiobjektschere(_guiereignisdaten*) {dobjektschere->aktivieren();};
void _hauptfenster::beiobjektzettel(_guiereignisdaten*) {dobjektzettel->aktivieren();};
void _hauptfenster::beiobjektfallschirm(_guiereignisdaten*) {dobjektfallschirm->aktivieren();};
void _hauptfenster::beiobjektzauberstab(_guiereignisdaten*) {dobjektzauberstab->aktivieren();};
void _hauptfenster::beiobjekttriebwerk(_guiereignisdaten*) {dobjekttriebwerk->aktivieren();};
void _hauptfenster::beiobjektgesundheit(_guiereignisdaten*) {dobjektgesundheit->aktivieren();};
void _hauptfenster::beiobjektreisszwecke(_guiereignisdaten*) {dobjektreisszwecke->aktivieren();};
void _hauptfenster::beiobjekthammer(_guiereignisdaten*) {dobjekthammer->aktivieren();};
void _hauptfenster::beiobjektgasbrenner(_guiereignisdaten*) {dobjektgasbrenner->aktivieren();};
void _hauptfenster::beiobjektschutzschild(_guiereignisdaten*) {dobjektschutzschild->aktivieren();};
void _hauptfenster::beiobjektschneidbrenner(_guiereignisdaten*) {dobjektschneidbrenner->aktivieren();}; 
void _hauptfenster::beiobjektschwarzesloch(_guiereignisdaten*) {dobjektschwarzesloch->aktivieren();};
void _hauptfenster::beiobjektmagnet(_guiereignisdaten*) {dobjektmagnet->aktivieren();};
void _hauptfenster::beiobjektpresslufthammer(_guiereignisdaten*) {dobjektpresslufthammer->aktivieren();};
void _hauptfenster::beiobjektteleporter(_guiereignisdaten*) {dobjektteleporter->aktivieren();};
void _hauptfenster::beiobjektgleitmittel(_guiereignisdaten*) {dobjektgleitmittel->aktivieren();};
void _hauptfenster::beiobjektgeld(_guiereignisdaten*) {dobjektgeld->aktivieren();};
void _hauptfenster::beiobjektsprungfeder(_guiereignisdaten*) {dobjektsprungfeder->aktivieren();};
void _hauptfenster::beiobjektskalierer(_guiereignisdaten*) {dobjektskalierer->aktivieren();};
void _hauptfenster::beiobjektpflanze(_guiereignisdaten*) {dobjektpflanze->aktivieren();};
void _hauptfenster::beiobjektobst(_guiereignisdaten*) {dobjektobst->aktivieren();};
void _hauptfenster::beiobjektdematerialisierung(_guiereignisdaten*) {dobjektdematerialisierung->aktivieren();};
void _hauptfenster::beiobjektdevisualisierung(_guiereignisdaten*) {dobjektdevisualisierung->aktivieren();};
void _hauptfenster::beiobjektinsektenspray(_guiereignisdaten*) {dobjektinsektenspray->aktivieren();};
void _hauptfenster::beiobjektfeuerloescher(_guiereignisdaten*) {dobjektfeuerloescher->aktivieren();};
void _hauptfenster::beiobjektsummer(_guiereignisdaten*) {dobjektsummer->aktivieren();};
void _hauptfenster::beiobjektblinker(_guiereignisdaten*) {dobjektblinker->aktivieren();};
void _hauptfenster::beiobjektbatterie(_guiereignisdaten*) {dobjektbatterie->aktivieren();};
void _hauptfenster::beiobjektpinsel(_guiereignisdaten*) {dobjektpinsel->aktivieren();};
void _hauptfenster::beiobjektbesen(_guiereignisdaten*) {dobjektbesen->aktivieren();};
void _hauptfenster::beiobjektlampe(_guiereignisdaten*) {dobjektlampe->aktivieren();};
void _hauptfenster::beiobjektkerze(_guiereignisdaten*) {dobjektkerze->aktivieren();};
void _hauptfenster::beiobjektgewicht(_guiereignisdaten*) {dobjektgewicht->aktivieren();};
void _hauptfenster::beiobjektgasmaske(_guiereignisdaten*) {dobjektgasmaske->aktivieren();};
void _hauptfenster::beiobjektschutzhelm(_guiereignisdaten*) {dobjektschutzhelm->aktivieren();};
void _hauptfenster::beiobjektspritze(_guiereignisdaten*) {dobjektspritze->aktivieren();};  

void _hauptfenster::beibodennormal(_guiereignisdaten*) {dbodennormal->aktivieren();};
void _hauptfenster::beibodenschalter(_guiereignisdaten*) {dbodenschalter->aktivieren();};
void _hauptfenster::beibodeninvers(_guiereignisdaten*) {dbodeninvers->aktivieren();};
void _hauptfenster::beibodenweltraum(_guiereignisdaten*) {dbodenweltraum->aktivieren();};
void _hauptfenster::beibodeneis(_guiereignisdaten*) {dbodeneis->aktivieren();};
void _hauptfenster::beibodensand(_guiereignisdaten*) {dbodensand->aktivieren();};
void _hauptfenster::beibodenschnee(_guiereignisdaten*) {dbodenschnee->aktivieren();};
void _hauptfenster::beibodenwiese(_guiereignisdaten*) {dbodenwiese->aktivieren();};
void _hauptfenster::beibodenwasser(_guiereignisdaten*) {dbodenwasser->aktivieren();};
void _hauptfenster::beibodensumpf(_guiereignisdaten*) {dbodensumpf->aktivieren();};
void _hauptfenster::beibodenlava(_guiereignisdaten*) {dbodenlava->aktivieren();};
void _hauptfenster::beibodenbeschleunigung(_guiereignisdaten*) {dbodenbeschleunigung->aktivieren();};
void _hauptfenster::beibodengradienz(_guiereignisdaten*) {dbodengradienz->aktivieren();};
void _hauptfenster::beibodentransport(_guiereignisdaten*) {dbodentransport->aktivieren();};
void _hauptfenster::beibodentotenkopf(_guiereignisdaten*) {dbodentotenkopf->aktivieren();}; 
//------------------------------ FIGUR ----------------------------------------------------
void _hauptfenster::beifigurkugel(_guiereignisdaten *){
                                if(corundwelt){
                                 dkugel->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Kugel anlegen können.");
};
void _hauptfenster::beifigurspinne(_guiereignisdaten *){
                                if(corundwelt){
                                 dspinne->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Spinne anlegen können.");
};
void _hauptfenster::beifigurorakel(_guiereignisdaten *){
                                if(corundwelt){
                                 dorakel->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie ein Orakel anlegen können.");
};
void _hauptfenster::beifigurhebweber(_guiereignisdaten*){
                                if(corundwelt){
                                 dhebweber->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie einen Hebweber anlegen können.");
}; 
void _hauptfenster::beifigurspringspinne(_guiereignisdaten*){
                                if(corundwelt){
                                 dspringspinne->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Springspinne anlegen können.");
}; 
void _hauptfenster::beifigurcatwiesel(_guiereignisdaten*){
                                if(corundwelt){
                                 dcatwiesel->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie ein Catwiesel anlegen können.");
}; 
void _hauptfenster::beifigurfliege(_guiereignisdaten*){
                                if(corundwelt){
                                 dfliege->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Fliege anlegen können.");
}; 
void _hauptfenster::beifigurmade(_guiereignisdaten*){
                                if(corundwelt){
                                 dmade->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Raupe anlegen können.");
}; 

//------------------------------ GRAVITATION ----------------------------------------------------
void _hauptfenster::beigravitation(_guiereignisdaten *){
                                if(corundwelt){
                                 dgravitation->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Gravitation anlegen können.");
};
void _hauptfenster::beiefeld(_guiereignisdaten *){
                                if(corundwelt){
                                 dfeldelektrostatisch->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie ein E-Feld anlegen können.");
};
void _hauptfenster::beibfeld(_guiereignisdaten *){
                                if(corundwelt){
                                 dfeldmagnetostatisch->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie ein B-Feld anlegen können.");
};

//------------------------------ PARTIKELQUELLE ----------------------------------------------------
void _hauptfenster::beipartikelquelleintern(_guiereignisdaten*){
                                if(corundwelt) {
                                 corundwelt->erzeugenpartikelsysteme();
                                 zeichnen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie die internen Partikelquellen anlegen können.");
};
void _hauptfenster::beipartikelquellesprite(_guiereignisdaten*){
                                if(corundwelt){
                                 dpartikelquellesprite->zeigen();
                                }else information("Hinweis","Sie müssen erst eine Welt anlegen, bevor Sie eine Partikelquelle anlegen können.");
};
//------------------------------ SYSTEM ----------------------------------------------------
void _hauptfenster::beigroessedummyoben(_guiereignisdaten *ep){
                                splittervertikal[0]->skalieren();                      
};
void _hauptfenster::beigroessedummyunten(_guiereignisdaten *ep){
                                splittervertikal[1]->skalieren();                      
};
void _hauptfenster::beigroesse(_guiereignisdaten *ep){
                                // ToolBar, StatusBar, tabwindow aktualisiern
                                toolbar->skalieren();
                                statusbar->skalieren();
                                _guirechteck<int>  rect=ClientRect<int>();
                                _guirechteck<int>  tb=toolbar->WindowRect<int>();
                                _guirechteck<int>  sb=statusbar->WindowRect<int>();
                                tabwindow->bewegen(rect.rechts() - 100, rect.oben() + tb.hoehe(), 100, rect.hoehe() - (tb.hoehe() + sb.hoehe()));
                                tabwindow->skalieren();                                
                                dummyganz->bewegen(rect.links(), rect.oben() + tb.hoehe(), rect.breite() - 100, rect.hoehe() - (tb.hoehe() + sb.hoehe())); 
                                splitterhorizontal->skalieren();          
                                splittervertikal[0]->skalieren();          
                                splittervertikal[1]->skalieren();          
};                                
void _hauptfenster::beiknopferzeugenbaum(_guiereignisdaten*){
                                if(corundwelt){
                                 corundwelt->erzeugenbaum();
                                 zeichnen();
                                }else information("Fehler","Keine Welt vorhanden.");
};
void _hauptfenster::einhaengendialog(_dynamischerdialog*d){
                                d->neusetzen(L"Programmeigenschaften bearbeiten");
                                d->loeschensektion(); 
                                d->addierensektion(L"Allgemein");
                                d->sektion(L"Allgemein")->offen(true);
                                d->editierbar(this);
                                d->einhaengen(L"Allgemein",L"Raster verwenden",rasterverwenden);
                                d->einhaengen(L"Allgemein",L"Raster zeichnen",rasterzeichnen);
                                d->einhaengen(L"Allgemein",L"Raster Teilung",rasterbreite);
                                d->einhaengen(L"Allgemein",L"Raster Snapping",snapping);
                                d->einhaengen(L"Allgemein",L"Gravitationsfeld zeichnen",gfeldzeichnen);
                                d->einhaengen(L"Allgemein",L"Magnetostatisches Feld zeichnen",bfeldzeichnen);
                                d->einhaengen(L"Allgemein",L"Elektrostatisches Feld zeichnen",efeldzeichnen);
                                d->einhaengen(L"Allgemein",L"Anzahl der Visualisierungen im Gravitationsfeld pro Achse",gfeldanzahl);
                                d->einhaengen(L"Allgemein",L"Anzahl der Visualisierungen im magnetostatischen Feld pro Achse",bfeldanzahl);
                                d->einhaengen(L"Allgemein",L"Anzahl der Visualisierungen im elektrostatischen Feld pro Achse",efeldanzahl);
                                d->einhaengen(L"Allgemein",L"Baum zeichnen",baumzeichnen);
                                d->einhaengenknopf<_hauptfenster>(L"Allgemein",L"Temporären Baum",L"erzeugen",this,&_hauptfenster::beiknopferzeugenbaum);
                                d->einhaengen(L"Allgemein",L"Debug Intersektion",debugintersektion);
                                d->einhaengen(L"Allgemein",L"Debug Sektorerzeugung",debugsektor);
                                d->einhaengen(L"Allgemein",L"Debug BSP",debugbsp);
                                d->einhaengen(L"Allgemein",L"Debug Portal",debugportal);
                                d->einhaengen(L"Allgemein",L"Debug Sichtbarkeiten",debugsichtbarkeit);
};
void _hauptfenster::auslesendialog(_dynamischerdialog*d){
                                d->auslesen(L"Allgemein",L"Raster verwenden",rasterverwenden);
                                d->auslesen(L"Allgemein",L"Raster zeichnen",rasterzeichnen);
                                d->auslesen(L"Allgemein",L"Raster Teilung",rasterbreite);
                                d->auslesen(L"Allgemein",L"Raster Snapping",snapping);
                                d->auslesen(L"Allgemein",L"Gravitationsfeld zeichnen",gfeldzeichnen);
                                d->auslesen(L"Allgemein",L"Magnetostatisches Feld zeichnen",bfeldzeichnen);
                                d->auslesen(L"Allgemein",L"Elektrostatisches Feld zeichnen",efeldzeichnen);
                                d->auslesen(L"Allgemein",L"Anzahl der Visualisierungen im Gravitationsfeld pro Achse",gfeldanzahl);
                                d->auslesen(L"Allgemein",L"Anzahl der Visualisierungen im magnetostatischen Feld pro Achse",bfeldanzahl);
                                d->auslesen(L"Allgemein",L"Anzahl der Visualisierungen im elektrostatischen Feld pro Achse",efeldanzahl);
                                d->auslesen(L"Allgemein",L"Baum zeichnen",baumzeichnen);
                                d->auslesen(L"Allgemein",L"Debug Intersektion",debugintersektion);
                                d->auslesen(L"Allgemein",L"Debug Sektorerzeugung",debugsektor);
                                d->auslesen(L"Allgemein",L"Debug BSP",debugbsp);
                                d->auslesen(L"Allgemein",L"Debug Portal",debugportal);
                                d->auslesen(L"Allgemein",L"Debug Sichtbarkeiten",debugsichtbarkeit);

};
//******************************************************************************************************************************************************************************************************
//                                                              H A U P T T O O L B A R
//******************************************************************************************************************************************************************************************************
_haupttoolbar::_haupttoolbar(_hauptfenster*hf):_guiwerkzeugleiste(hf){
                                int number = 15; 
                                // ---------------------------------------------------------------------                                
                                hauptfenster=hf;
                                knopfgroesse(16,16); 
                                addierenbitmapsystem(IDB_STD_SMALL_COLOR);   // da ist öffnen, speichern, rückgängig usw. drin
                                addierenbitmapresource(1,TBBITMAP_HINTEN); 
                                addierenbitmapresource(1,TBBITMAP_NORMAL); 
                                addierenbitmapresource(1,TBBITMAP_VORNE); 
                                addierenbitmapresource(1,TBBITMAP_ALLE); 
                                addierenbitmapresource(1,TBBITMAP_TILES); 
                                addierenbitmapresource(1,TBBITMAP_TILEGROUPS); 
                                addierenbitmapresource(1,TBBITMAP_ENTITIES);
                                addierenbitmapresource(1,ANWAHLNETZ);
                                addierenbitmapresource(1,ANWAHLPOLYGON);
                                addierenbitmapresource(1,ANWAHLKANTE);
                                addierenbitmapresource(1,ANWAHLVERTEX);
                                addierenbitmapresource(1,TESTKUGEL);
                                addierenbitmapresource(1,TESTKUGEL2);
                                separator(3);
                                new _guiwerkzeugleisteknopf(this, STD_FILENEW, L"Neue Szene erstellen", new _guiereignisCommand<_hauptfenster>(hf,&_hauptfenster::beiweltneu)); 
                                new _guiwerkzeugleisteknopf(this, STD_FILEOPEN, L"Szene laden", new _guiereignisCommand<_hauptfenster>(hf,&_hauptfenster::beiweltladen)); 
                                new _guiwerkzeugleisteknopf(this, STD_FILESAVE, L"Szene speichern", new _guiereignisCommand<_hauptfenster>(hf,&_hauptfenster::beiweltspeichern)); 
                                new _guiwerkzeugleisteknopf(this, 26, L"Testen", new _guiereignisCommand<_hauptfenster>(hf,&_hauptfenster::beiwelttesten)); 
                                new _guiwerkzeugleisteknopf(this, 27, L"Testen des Weltverbundes", new _guiereignisCommand<_hauptfenster>(hf,&_hauptfenster::beiwelttestenverbund)); 
                                new _guiwerkzeugleisteknopf(this, 26, L"Testen Spinnmania", new _guiereignisCommand<_hauptfenster>(hf,&_hauptfenster::beiwelttestenspinnmania)); 

                                separator(24);
                                netzanwahl=new _guiwerkzeugleisteknopf(this, 22, L"Anwahlmodus Netz", new _guiereignisCommand<_haupttoolbar>(this,&_haupttoolbar::beinetzanwahl)); 
                                polygonanwahl=new _guiwerkzeugleisteknopf(this, 23, L"Anwahlmodus Polygon", new _guiereignisCommand<_haupttoolbar>(this,&_haupttoolbar::beipolygonanwahl)); 
                                kantenanwahl=new _guiwerkzeugleisteknopf(this, 24, L"Anwahlmodus Kante", new _guiereignisCommand<_haupttoolbar>(this,&_haupttoolbar::beikantenanwahl)); 
                                vertexanwahl=new _guiwerkzeugleisteknopf(this, 25, L"Anwahlmodus Vertex", new _guiereignisCommand<_haupttoolbar>(this,&_haupttoolbar::beivertexanwahl)); 
                                polygonanwahl->gesetzt(true);
                                separator();
};
_haupttoolbar::~_haupttoolbar(){
};
void _haupttoolbar::beinetzanwahl(_guiereignisdaten*){
                                netzanwahl->gesetzt(true);
                                polygonanwahl->gesetzt(false);
                                kantenanwahl->gesetzt(false);
                                vertexanwahl->gesetzt(false);
                                _liste<_netz> ln;
                                _listenknoten<_netz>*nit;
                                _listenknoten<_polygon>*pit;
                                _listenknoten<_vertex>*vit;
                                _listenknoten<_verbindervertexpolygon>*cit;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,ln.einhaengenunredundant(nit->objekt()));
                                iterierenliste(&hauptfenster->anwahlpolygonliste,pit,ln.einhaengenunredundant(pit->objekt()->netz()));
                                iterierenliste(&hauptfenster->anwahlvertexliste,vit,ln.einhaengenunredundant(vit->objekt()->netz()));
                                iterierenliste(&hauptfenster->anwahlkanteliste,cit,ln.einhaengenunredundant(cit->objekt()->vertex()->netz()));
                                hauptfenster->loeschenanwahl();
                                iterierenliste(&ln,nit,hauptfenster->anwahlnetzliste.einhaengen(nit->objekt()));
                                hauptfenster->zeichnen();
};
void _haupttoolbar::beipolygonanwahl(_guiereignisdaten*){
                                netzanwahl->gesetzt(false);
                                polygonanwahl->gesetzt(true);
                                kantenanwahl->gesetzt(false);
                                vertexanwahl->gesetzt(false);
                                _liste<_polygon> l;
                                _listenknoten<_netz>*nit;
                                _listenknoten<_polygon>*pit;
                                _listenknoten<_vertex>*vit;
                                _listenknoten<_verbindervertexpolygon>*cit;
                                _verbindervertexpolygon*c;
                                _polygon*p;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,iterierenliste(nit->objekt(),p,l.einhaengenunredundant(p)));
                                iterierenliste(&hauptfenster->anwahlpolygonliste,pit,l.einhaengenunredundant(pit->objekt()));
                                iterierenliste(&hauptfenster->anwahlvertexliste,vit,iterierenliste(vit->objekt(),pit,l.einhaengenunredundant(pit->objekt())));
                                iterierenliste(&hauptfenster->anwahlkanteliste,cit,l.einhaengenunredundant(cit->objekt()->polygon()));
                                hauptfenster->loeschenanwahl();
                                iterierenliste(&l,pit,hauptfenster->anwahlpolygonliste.einhaengen(pit->objekt()));
                                hauptfenster->zeichnen();
};
void _haupttoolbar::beikantenanwahl(_guiereignisdaten*){
                                netzanwahl->gesetzt(false);
                                polygonanwahl->gesetzt(false);
                                kantenanwahl->gesetzt(true);
                                vertexanwahl->gesetzt(false);
                                _liste<_verbindervertexpolygon> l;
                                _listenknoten<_netz>*nit;
                                _listenknoten<_polygon>*pit;
                                _listenknoten<_vertex>*vit;
                                _listenknoten<_verbindervertexpolygon>*cit;
                                _verbindervertexpolygon*c;
                                _polygon*p;
                                _vertex*v;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,iterierenliste(nit->objekt(),p,iterierenliste(p,vit,  l.einhaengenunredundant(static_cast<_verbindervertexpolygon*>(vit)) )));
                                iterierenliste(&hauptfenster->anwahlpolygonliste,pit,iterierenliste(pit->objekt(),vit,  l.einhaengenunredundant(static_cast<_verbindervertexpolygon*>(vit))));
                                iterierenliste(&hauptfenster->anwahlvertexliste,vit,iterierenliste(vit->objekt(),pit,l.einhaengenunredundant(static_cast<_verbindervertexpolygon*>(pit))));
                                iterierenliste(&hauptfenster->anwahlkanteliste,cit,l.einhaengenunredundant(cit->objekt()));
                                hauptfenster->loeschenanwahl();
                                iterierenliste(&l,cit,hauptfenster->anwahlkanteliste.einhaengen(cit->objekt()));
                                hauptfenster->zeichnen();
};
void _haupttoolbar::beivertexanwahl(_guiereignisdaten*){
                                netzanwahl->gesetzt(false);
                                polygonanwahl->gesetzt(false);
                                kantenanwahl->gesetzt(false);
                                vertexanwahl->gesetzt(true);
                                _liste<_vertex> l;
                                _listenknoten<_netz>*nit;
                                _listenknoten<_polygon>*pit;
                                _listenknoten<_vertex>*vit;
                                _listenknoten<_verbindervertexpolygon>*cit;
                                _verbindervertexpolygon*c;
                                _polygon*p;
                                _vertex*v;
                                iterierenliste(&hauptfenster->anwahlnetzliste,nit,iterierenliste(nit->objekt(),p,iterierenliste(p,vit,l.einhaengenunredundant(vit->objekt()))));
                                iterierenliste(&hauptfenster->anwahlpolygonliste,pit,iterierenliste(pit->objekt(),vit,l.einhaengenunredundant(vit->objekt())));
                                iterierenliste(&hauptfenster->anwahlvertexliste,vit,l.einhaengenunredundant(vit->objekt()));
                                iterierenliste(&hauptfenster->anwahlkanteliste,cit,l.einhaengenunredundant(cit->objekt()->vertex());l.einhaengenunredundant(cit->objekt()->naechstervertex()));                                  
                                hauptfenster->loeschenanwahl();
                                iterierenliste(&l,vit,hauptfenster->anwahlvertexliste.einhaengen(vit->objekt()));
                                hauptfenster->zeichnen();
};
//******************************************************************************************************************************************************************************************************
//                                                              H A U P T F U N K T I O N 
//******************************************************************************************************************************************************************************************************
int WINAPI WinMain(HINSTANCE hi,HINSTANCE,LPSTR,int){
                                //Leak-Tracer
                                //#ifdef _DEBUG
                                //_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
                                //_CrtSetBreakAlloc(4852);
                                //_CrtSetBreakAlloc(19805);  // Kann man verwenden um ein Mem-Leak zu finden
                                //#endif
                                L=new _logbuch("_corundeditorlogbuch.txt");
                                _guikonfiguration config;
                                _hauptfenster*hf ;
                                //-------------------------------------------
                                //try{
                                 config.icon=I_PROJEKTOR;
                                 guiinitialisieren(&config);  // Icon kannst du vorher setzen
                                 hf= new _hauptfenster(L"Corund Editor");
                                _win::_zeit*uhr=new _win::_zeit();
                                 guianimieren();                                 
								//}
								//     catch(const char*c){
								//      GUI::Error();
								//      L->schreiben("Fehler : ",c);
								//      return(-1);
								//     }
								//     catch(...)
								//     {
								//      GUI::Error();
								//      L->schreiben("sontiges Problem ");
								//      return(-1);
								//     }
                                //delete hf;
                                if(hf->corundwelt) delete hf->corundwelt;
                                hf->corundwelt=0;
                                guideinitialisieren();
								delete L;
                                return(0);
};