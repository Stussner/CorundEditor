#include "../hpp/_corundspeicherbar.hpp"
/*
template<class T>void speichernstein(_dateispeicherbartext*datei,_corundwelt*ow,const _zeichenkette<char>&typ,const _zeichenkette<char>&name){
                                                                _corundstein*osit;
                                                                unsigned int c=0;
                                                                char s[1024];
                                                                if(ow->anfang(osit))do{
                                                                 if(osit->markierung==0){
                                                                  T*konkret;
                                                                  konkret=dynamic_cast<T*>(osit);
                                                                  if(konkret){
                                                                   _speicherbardynamisch<T>*sd;
                                                                   sd=new _speicherbardynamisch<T>(datei,konkret);
                                                                   sd->typ(typ);
                                                                   _itoa(c++,s,16);
                                                                   sd->name(name+s);
                                                                   osit->markierung=1;
                                                                   //L->schreiben("osittyp=",gettypename<T>(konkret));
                                                                  };
                                                                 };
                                                                }while(ow->naechstes(osit));
};                                      
                */      
template<class T>void speichernnetz(_dateispeicherbartext*datei,_corundwelt*ow,_netz*netz,_speicherbardynamisch<T>*besitzer,const _zeichenkette<char>&name){
                                                                _polygon*polygon;
                                                                _vertex*vertex;
                                                                _verbindervertexpolygon*connector;
                                                                _speicherbardynamisch<_netz >*sdmesh;
                                                                _speicherbardynamisch<_material<_tg> >*sdmeshmaterial;
                                                                _speicherbardynamisch<_polygon >*sdpolygon;
                                                                _speicherbardynamisch<_oberflaeche<_tg> >*sdpolygonoberflaeche;
                                                                _speicherbardynamisch<_vertex >*sdvertex;
                                                                _speicherbardynamisch<_verbindervertexpolygon >*sdconnector;
                                                                unsigned int pi;
                                                                unsigned int vi;
                                                                unsigned int ci;
                                                                _zeichenkette<char> polygonname="p";
                                                                _zeichenkette<char> vertexname="v";
                                                                _zeichenkette<char> connectorname="c";
                                                                char s[2048];
                                                                //------------------
                                                                sdmesh=new _speicherbardynamisch<_netz >(datei,besitzer,netz);
                                                                sdmesh->typ("_netz");
                                                                sdmesh->name(name);
                                                                sdmeshmaterial=new _speicherbardynamisch<_material<_tg> >(datei,sdmesh,netz);
                                                                sdmeshmaterial->typ("_material");
                                                                //sdmeshmaterial->name(name);
                                                                pi=0;
                                                                if(netz->anfang(polygon))do{
                                                                 sdpolygon=new _speicherbardynamisch<_polygon >(datei,sdmesh,polygon);
                                                                 sdpolygon->typ("_polygon");
                                                                 _itoa(pi,s,16);
                                                                 sdpolygon->name(polygonname+s);
                                                                 sdpolygonoberflaeche=new _speicherbardynamisch<_oberflaeche<_tg> >(datei,sdpolygon,polygon);
                                                                 sdpolygonoberflaeche->typ("_oberflaeche");
                                                                 //sdpolygonoberflaeche->name(name);
                                                                   ci=0;
                                                                   _listenknoten<_vertex>*lnv;
                                                                   if(polygon->anfang(lnv))do{
                                                                    connector=static_cast<_verbindervertexpolygon*>(lnv);
                                                                    sdconnector=new _speicherbardynamisch<_verbindervertexpolygon >(datei,sdpolygon,connector);
                                                                    sdconnector->typ("_verbinder");
                                                                    _itoa(ci,s,16);
                                                                    sdconnector->name(connectorname+s);
                                                                    ci++;
                                                                   }while(polygon->naechstes(lnv));
                                                                 
                                                                 
                                                                 pi++;
                                                                }while(netz->naechstes(polygon));
                                                                vi=0;
                                                                netz->markierungvertex(0);
                                                                if(netz->anfang(vertex))do{
                                                                 sdvertex=new _speicherbardynamisch<_vertex >(datei,sdmesh,vertex);
                                                                 sdvertex->typ("_vertex");
                                                                 _itoa(vi,s,16);
                                                                 sdvertex->name(vertexname+s);
                                                                 vi++;
                                                                }while(netz->naechstes(vertex));
                                                                netz->markierung(0);
                                                                /*
                                                                netz->markierungvertex(1);
                                                                if(netz->anfang(polygon))do{
                                                                 vertex=polygon->vertex();
                                                                 if(vertex)do{
                                                                  if(vertex->markierung()==1){
                                                                   sdvertex=new _speicherbardynamisch<_vertex >(datei,sdmesh,vertex);
                                                                   sdvertex->typ("_vertex");
                                                                   _itoa(vi,s,16);
                                                                   sdvertex->name(vertexname+s);
                                                                   vi++;
                                                                   vertex->markierung(0);
                                                                  };
                                                                  vertex=vertex->naechstes(polygon);
                                                                 }while(vertex!=polygon->vertex());
                                                                }while(netz->naechstes(polygon));
                                                                netz->markierung(0);
                                                                */
};
                
template<class T>void speichernstein(_dateispeicherbartext*datei,_corundwelt*ow,const _zeichenkette<char>&typ,const _zeichenkette<char>&name){
                                                                _corundstein*osit;
                                                                
                                                                unsigned int c=0;
                                                                char s[1024];
                                                                if(ow->anfang(osit))do{
                                                                 if(osit->markierung==1){
                                                                  T*konkret;
                                                                  konkret=dynamic_cast<T*>(osit);
                                                                  if(konkret){
                                                                   _speicherbardynamisch<T>*sd;
                                                                   sd=new _speicherbardynamisch<T>(datei,ow->_basis::_speicherbarargument<_corundwelt>::speicherbar(),konkret);
                                                                   sd->typ(typ);
                                                                   _itoa(c++,s,16);
                                                                   sd->name(name+s);
                                                                   
                                                                   _speicherbardynamisch<_corundstein>*sdos;
                                                                   sdos=new _speicherbardynamisch<_corundstein>(datei,sd,konkret);
                                                                   sdos->typ("_corundstein");
                                                                   sdos->name("os");
                                                                   speichernnetz<_corundstein>(datei,ow,osit,sdos,"n");
                                                                   sd->holennamenqualifikation(konkret->dateiqualifikation);
                                                                   osit->markierung=0;
                                                                  };
                                                                 };
                                                                }while(ow->naechstes(osit));
};             
                                                   
void speichernstein(_dateispeicherbartext*datei,_corundwelt*ow){
                                                                _corundstein*osit;
                                                                unsigned int c=0;
                                                                char s[1024];
                                                                if(ow->anfang(osit))do{
                                                                 if(osit->markierung==1){
                                                                  _speicherbardynamisch<_corundstein>*sdos;
                                                                  sdos=new _speicherbardynamisch<_corundstein>(datei,ow->_basis::_speicherbarargument<_corundwelt>::speicherbar(),osit);
                                                                  sdos->typ("_corundstein");
                                                                  _itoa(c++,s,16);
                                                                  sdos->name(_zeichenkette<char>("os")+s);
                                                                  speichernnetz<_corundstein>(datei,ow,osit,sdos,"n");
                                                                  osit->markierung=0;
                                                                 };
                                                                }while(ow->naechstes(osit));
};        
template<class T>void speichernobjekt(_dateispeicherbartext*datei,_corundwelt*ow,const _zeichenkette<char>&typ,const _zeichenkette<char>&name){
                                                                _corundobjekt*osit;
                                                                
                                                                unsigned int c=0;
                                                                char s[1024];
                                                                if(ow->anfang(osit))do{
                                                                 if(osit->markierung==1){
                                                                  T*konkret;
                                                                  konkret=dynamic_cast<T*>(osit);
                                                                  if(konkret){
                                                                   _speicherbardynamisch<T>*sd;
                                                                   sd=new _speicherbardynamisch<T>(datei,ow->_basis::_speicherbarargument<_corundwelt>::speicherbar(),konkret);
                                                                   sd->typ(typ);
                                                                   _itoa(c++,s,16);
                                                                   sd->name(name+s);
                                                                   _speicherbardynamisch<_corundobjekt>*sdos;
                                                                   sdos=new _speicherbardynamisch<_corundobjekt>(datei,sd,konkret);
                                                                   sdos->typ("_corundobjekt");
                                                                   sdos->name("co");
                                                                   //speichernnetz<_corundobjekt>(datei,ow,osit,sdos,"n");
                                                                   _netz*netz=osit;
                                                                   netz->markierung(0);
                                                                   osit->markierung=0;
                                                                   sd->holennamenqualifikation(konkret->dateiqualifikation);
                                                                  };
                                                                 };
                                                                }while(ow->naechstes(osit));
};                 
template<class T>void speichernboden(_dateispeicherbartext*datei,_corundwelt*ow,const _zeichenkette<char>&typ,const _zeichenkette<char>&name){
                                                                _corundboden*cbit;
                                                                
                                                                unsigned int c=0;
                                                                char s[1024];
                                                                if(ow->anfang(cbit))do{
                                                                 if(cbit->markierung==1){
                                                                  T*konkret;
                                                                  konkret=dynamic_cast<T*>(cbit);
                                                                  if(konkret){
                                                                   _speicherbardynamisch<T>*sd;
                                                                   sd=new _speicherbardynamisch<T>(datei,ow->_basis::_speicherbarargument<_corundwelt>::speicherbar(),konkret);
                                                                   sd->typ(typ);
                                                                   _itoa(c++,s,16);
                                                                   sd->name(name+s);
                                                                   _speicherbardynamisch<_corundboden>*sdcb;
                                                                   sdcb=new _speicherbardynamisch<_corundboden>(datei,sd,konkret);
                                                                   sdcb->typ("_corundboden");
                                                                   sdcb->name("cb");
                                                                   speichernnetz<_corundboden>(datei,ow,cbit,sdcb,"n");
                                                                   sd->holennamenqualifikation(konkret->dateiqualifikation);
                                                                   cbit->markierung=0;
                                                                  };
                                                                 };
                                                                }while(ow->naechstes(cbit));
};                                                  
void corundweltspeichern(_hauptfenster*hf,_zeichenkette<char> fn,_corundwelt*ow){
                                                                
                                                                _speicherbardynamisch<_welt >*sdworld;
                                                                //_speicherbardynamisch<_netz >*sdmesh;
                                                                //_speicherbardynamisch<_polygon >*sdpolygon;
                                                                //_speicherbardynamisch<_vertex >*sdvertex;
                                                                //_speicherbardynamisch<_verbindervertexpolygon >*sdconnector;
                                                               // _speicherbardynamisch<_texturvektor<_tg> >*sdtexturevector;
                                                                _speicherbardynamisch<_bild<_tb> >*sdmap;
                                                                //_speicherbardynamisch<_bildtga<_to> >*sdmaptga;
                                                                _speicherbardynamisch<_textur<_tb> >*sdtexture;
                                                                _speicherbardynamisch<_licht<_tg,_to> >*sdlight;
                                                                _speicherbardynamisch<_gravitation<_tg> >*sdgravitation;
                                                                _speicherbardynamisch<_partikelquellesprite >*sdpartikelquellesprite;
                                                                _speicherbardynamisch<_kamera<_tg> >*sdcamera;
                                                                _speicherbardynamisch<_partition::_zone >*sdzone;
                                                                _speicherbardynamisch<_partition::_ebene >*sdplane;
                                                                _speicherbardynamisch<_partition::_sektor >*sdsector;
                                                                _speicherbardynamisch<_partition::_polygon >*sdppolygon;
                                                                _speicherbardynamisch<_partition::_vertex >*sdpvertex;
                                                                _welt*w=ow->welt;
                                                                _netz*netz;
                                                                //_polygon*polygon;
                                                                //_vertex*vertex;
                                                                //_verbindervertexpolygon*connector;
                                                                _bild<_tb>*bild;
                                                                //_bildtga<_to>*maptga;
                                                                _textur<_tb>*textur;
                                                                _licht<_tg,_to>*light;
                                                                _gravitation<_tg>*gravitation;
                                                                _feldelektrostatisch<_tg>*efeld;
                                                                _feldmagnetostatisch<_tg>*bfeld;
                                                                 
                                                                _partikelquellesprite*partikelquellesprite;
                                                                _kamera<_tg>*camera;
                                                                _partition::_zone*zone;
                                                                _partition::_ebene*ebene;
                                                                _partition::_sektor*sektor;
                                                                _partition::_polygon*ppolygon;
                                                                _partition::_vertex*pvertex;
                                                                unsigned int mi;
                                                                //unsigned int pi;
                                                                //unsigned int vi;
                                                                //unsigned int ci;
                                                                //unsigned int mtgai;
                                                                unsigned int ti;
                                                                unsigned int li;
                                                                unsigned int gi;
                                                                unsigned int pqi;
                                                                unsigned int cami;
                                                                unsigned int zi;
                                                                unsigned int pli;
                                                                unsigned int si;
                                                                unsigned int ppi;
                                                                unsigned int pvi;
                                                                _zeichenkette<char> worldtype="_welt";
                                                                _zeichenkette<char> meshtype="_netz";
                                                                _zeichenkette<char> polygontype="_polygon";
                                                                _zeichenkette<char> vertextype="_vertex";
                                                                _zeichenkette<char> connectortype="_verbinder";
                                                                _zeichenkette<char> texturevectortype="_texturvektor";
                                                                _zeichenkette<char> maptgatype="_bild";
                                                                _zeichenkette<char> texturetype="_textur";
                                                                _zeichenkette<char> lighttype="_licht";
                                                                _zeichenkette<char> clighttype="_clicht";
                                                                _zeichenkette<char> gravitationtype="_gravitation";
                                                                _zeichenkette<char> partikelquellespritetype="_partikelquellesprite";
                                                                _zeichenkette<char> cameratype="_kamera";
                                                                _zeichenkette<char> zonetype="_zone";
                                                                _zeichenkette<char> planetype="_ebene";
                                                                _zeichenkette<char> sectortype="_sektor";
                                                                _zeichenkette<char> ppolygontype="_partitionpolygon";
                                                                _zeichenkette<char> pvertextype="_partitionvertex";
                                                                _zeichenkette<char> worldname="w";
                                                                _zeichenkette<char> meshname="m";
                                                                _zeichenkette<char> polygonname="p";
                                                                _zeichenkette<char> vertexname="v";
                                                                _zeichenkette<char> connectorname="c";
                                                                _zeichenkette<char> texturevectorname="tv";
                                                                _zeichenkette<char> maptganame="mtga";
                                                                _zeichenkette<char> texturename="tx";
                                                                _zeichenkette<char> lightname="l";
                                                                _zeichenkette<char> clightname="cl";
                                                                _zeichenkette<char> gravitationname="g";
                                                                _zeichenkette<char> efeldname="ef";
                                                                _zeichenkette<char> bfeldname="bf";
                                                                _zeichenkette<char> partikelquellespritename="pq";
                                                                _zeichenkette<char> cameraname="cam";
                                                                _zeichenkette<char> zonename="z";
                                                                _zeichenkette<char> planename="pl";
                                                                _zeichenkette<char> sectorname="s";
                                                                _zeichenkette<char> ppolygonname="pp";
                                                                _zeichenkette<char> pvertexname="pv";
                                                                char s[2048];
                                                                //------------------------------------------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Dateiknoten werden angelegt ...");
                                                                _dateispeicherbartext datei(fn);
                                                                //vorbereiten, alles auf eins markieren
                                                                ow->welt->markierungnetz(1);
                                                                _corundstein*osit;
                                                                if(ow->anfang(osit))do{
                                                                 osit->markierung=1;
                                                                }while(ow->naechstes(osit));
                                                                _corundobjekt*coit;
                                                                if(ow->anfang(coit))do{
                                                                 coit->markierung=1;
                                                                }while(ow->naechstes(coit));
                                                                _corundboden*cbit;
                                                                if(ow->anfang(cbit))do{
                                                                 cbit->markierung=1;
                                                                }while(ow->naechstes(cbit));
                                                                //--------------------------corundWELT--------------------------------------------
                                                                _speicherbardynamisch<_corundwelt>*sdow;
                                                                sdow=new _speicherbardynamisch<_corundwelt>(&datei,ow);
                                                                sdow->typ("_corundwelt");
                                                                sdow->name("ow");
                                                                //ow->speichername=fn;
                                                                //--------------------------KNOTEN---------------------------------------------
                                                                _corundknoten*knoit;
                                                                unsigned int kni=0;
                                                                _speicherbardynamisch<_corundknoten>*sdknoten;
                                                                if(ow->anfang(knoit))do{
                                                                 sdknoten=new _speicherbardynamisch<_corundknoten >(&datei,sdow,knoit);
                                                                 _itoa(kni,s,16);
                                                                 sdknoten->name(_zeichenkette<char>("ck")+s);
                                                                 sdknoten->typ("_corundknoten");
                                                                 kni++;
                                                                }while(ow->naechstes(knoit));
                                                                //--------------------------STEINE--------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Steine werden speicherbar gemacht ...");
                                                                speichernstein<_corundsteincorund>(&datei,ow,"_corundsteincorund","oso");
                                                                speichernstein<_corundsteingummiband>(&datei,ow,"_corundsteingummiband","osgb");
                                                                speichernstein<_corundsteinschere>(&datei,ow,"_corundsteinschere","osschere");
                                                                speichernstein<_corundsteinschieb>(&datei,ow,"_corundsteinschieb","osschieb");
                                                                speichernstein<_corundsteinboulder>(&datei,ow,"_corundsteinboulder","osboulder");
                                                                speichernstein<_corundsteinrotation>(&datei,ow,"_corundsteinrotation","osrotation");
                                                                speichernstein<_corundsteinimpuls>(&datei,ow,"_corundsteinimpuls","osimpuls");
                                                                speichernstein<_corundsteinelektrisch>(&datei,ow,"_corundsteinelektrisch","oselektrisch");
                                                                speichernstein<_corundsteinerdung>(&datei,ow,"_corundsteinerdung","oserdung");
                                                                speichernstein<_corundsteinbeschleunigung>(&datei,ow,"_corundsteinbeschleunigung","osb");
                                                                speichernstein<_corundsteintotenkopf>(&datei,ow,"_corundsteintotenkopf","ostot");
                                                                speichernstein<_corundsteintor>(&datei,ow,"_corundsteintor","ost");
                                                                speichernstein<_corundsteinschalter>(&datei,ow,"_corundsteinschalter","oss");
                                                                speichernstein<_corundsteinkugelgen>(&datei,ow,"_corundsteinkugelgen","oskugelgen");
                                                                speichernstein<_corundsteindach>(&datei,ow,"_corundsteindach","osdach");
                                                                speichernstein<_corundsteinflak>(&datei,ow,"_corundsteinflak","osflak");
                                                                speichernstein<_corundsteinausgang>(&datei,ow,"_corundsteinausgang","osausgang");
                                                                speichernstein<_corundsteinsenker>(&datei,ow,"_corundsteinsenker","ossenker");
                                                                speichernstein<_corundsteinlaser>(&datei,ow,"_corundsteinlaser","oslaser");
                                                                speichernstein<_corundsteinspiegel>(&datei,ow,"_corundsteinspiegel","osspiegel");
                                                                speichernstein<_corundsteinschloss>(&datei,ow,"_corundsteinschloss","osschloss");
                                                                speichernstein<_corundsteinereignis>(&datei,ow,"_corundsteinereignis","osereignis");
                                                                speichernstein<_corundsteingerissen>(&datei,ow,"_corundsteingerissen","osgerissen");
                                                                speichernstein<_corundsteinspuck>(&datei,ow,"_corundsteinspuck","osspuck");
                                                                speichernstein<_corundsteintauscher>(&datei,ow,"_corundsteintauscher","ostauscher");
                                                                speichernstein<_corundsteinmagnetisch>(&datei,ow,"_corundsteinmagnetisch","osmag");
                                                                speichernstein<_corundsteindieb>(&datei,ow,"_corundsteindieb","osdieb");
                                                                speichernstein<_corundsteinfliegengen>(&datei,ow,"_corundsteinfliegengen","osfligen");
                                                                speichernstein<_corundsteinspinnengen>(&datei,ow,"_corundsteinspinnengen","osspigen");
                                                                speichernstein<_corundsteinshogun>(&datei,ow,"_corundsteinshogun","osshogun");
                                                                speichernstein<_corundsteinpuzzle>(&datei,ow,"_corundsteinpuzzle","ospuzzle");
                                                                speichernstein<_corundsteingas>(&datei,ow,"_corundsteingas","osgas");
                                                                speichernstein<_corundsteinkombinationsschloss>(&datei,ow,"_corundsteinkombinationsschloss","oskschloss");
                                                                speichernstein<_corundsteindrehkreuz>(&datei,ow,"_corundsteindrehkreuz","osdk");                                                                 
                                                                speichernstein<_corundsteineinbahn>(&datei,ow,"_corundsteineinbahn","oseinbahn");                                                                 
                                                                
                                                                speichernstein(&datei,ow);
                                                                //--------------------------OBJEKTE--------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Objekte werden speicherbar gemacht ...");
                                                                speichernobjekt<_corundobjektersatz>(&datei,ow,"_corundobjektersatz","coe");
                                                                speichernobjekt<_corundobjektschluessela>(&datei,ow,"_corundobjektschluessela","cosa");
                                                                speichernobjekt<_corundobjektbombe>(&datei,ow,"_corundobjektbombe","cobo");
                                                                speichernobjekt<_corundobjektdynamit>(&datei,ow,"_corundobjektdynamit","cody");
                                                                speichernobjekt<_corundobjektmine>(&datei,ow,"_corundobjektmine","comi");
                                                                speichernobjekt<_corundobjektsteinpille>(&datei,ow,"_corundobjektsteinpille","cosp");
                                                                speichernobjekt<_corundobjektalkohol>(&datei,ow,"_corundobjektalkohol","coal");
                                                                speichernobjekt<_corundobjektbungeeseil>(&datei,ow,"_corundobjektbungeeseil","cobs");
                                                                speichernobjekt<_corundobjektschere>(&datei,ow,"_corundobjektschere","cosc");
                                                                speichernobjekt<_corundobjektzettel>(&datei,ow,"_corundobjektzettel","coze");
                                                                speichernobjekt<_corundobjektfallschirm>(&datei,ow,"_corundobjektfallschirm","cofa");
                                                                speichernobjekt<_corundobjektzauberstab>(&datei,ow,"_corundobjektzauberstab","coza");
                                                                speichernobjekt<_corundobjekttriebwerk>(&datei,ow,"_corundobjekttriebwerk","cotr");
                                                                speichernobjekt<_corundobjektgesundheit>(&datei,ow,"_corundobjektgesundheit","coge"); 
                                                                speichernobjekt<_corundobjektreisszwecke>(&datei,ow,"_corundobjektreisszwecke","core");
                                                                speichernobjekt<_corundobjekthammer>(&datei,ow,"_corundobjekthammer","coha");
                                                                speichernobjekt<_corundobjektgasbrenner>(&datei,ow,"_corundobjektgasbrenner","coga");
                                                                speichernobjekt<_corundobjektschutzschild>(&datei,ow,"_corundobjektschutzschild","coschu");
                                                                speichernobjekt<_corundobjektschneidbrenner>(&datei,ow,"_corundobjektschneidbrenner","coschneid");
                                                                speichernobjekt<_corundobjektschwarzesloch>(&datei,ow,"_corundobjektschwarzesloch","cosl");
                                                                speichernobjekt<_corundobjektmagnet>(&datei,ow,"_corundobjektmagnet","comag");
                                                                speichernobjekt<_corundobjektpresslufthammer>(&datei,ow,"_corundobjektpresslufthammer","coplh");
                                                                speichernobjekt<_corundobjektteleporter>(&datei,ow,"_corundobjektteleporter","cotp");
                                                                speichernobjekt<_corundobjektgleitmittel>(&datei,ow,"_corundobjektgleitmittel","cogm");
                                                                speichernobjekt<_corundobjektgeld>(&datei,ow,"_corundobjektgeld","cogeld");
                                                                speichernobjekt<_corundobjektsprungfeder>(&datei,ow,"_corundobjektsprungfeder","cospru");
                                                                speichernobjekt<_corundobjektskalierer>(&datei,ow,"_corundobjektskalierer","coskal");
                                                                speichernobjekt<_corundobjektpflanze>(&datei,ow,"_corundobjektpflanze","copfl");
                                                                speichernobjekt<_corundobjektobst>(&datei,ow,"_corundobjektobst","coobst");
                                                                speichernobjekt<_corundobjektdematerialisierung>(&datei,ow,"_corundobjektdematerialisierung","codemat");
                                                                speichernobjekt<_corundobjektdevisualisierung>(&datei,ow,"_corundobjektdevisualisierung","codevis");
                                                                speichernobjekt<_corundobjektinsektenspray>(&datei,ow,"_corundobjektinsektenspray","coins");
                                                                speichernobjekt<_corundobjektfeuerloescher>(&datei,ow,"_corundobjektfeuerloescher","cofeuer");
                                                                speichernobjekt<_corundobjektsummer>(&datei,ow,"_corundobjektsummer","cosummer");
                                                                speichernobjekt<_corundobjektblinker>(&datei,ow,"_corundobjektblinker","coblinker");
                                                                speichernobjekt<_corundobjektbatterie>(&datei,ow,"_corundobjektbatterie","cobatt");
                                                                speichernobjekt<_corundobjektpinsel>(&datei,ow,"_corundobjektpinsel","copinsel");
                                                                speichernobjekt<_corundobjektbesen>(&datei,ow,"_corundobjektbesen","cobesen");
                                                                speichernobjekt<_corundobjektlampe>(&datei,ow,"_corundobjektlampe","colampe");
                                                                speichernobjekt<_corundobjektkerze>(&datei,ow,"_corundobjektkerze","cokerze");
                                                                speichernobjekt<_corundobjektgewicht>(&datei,ow,"_corundobjektgewicht","cogewicht");
                                                                speichernobjekt<_corundobjektgasmaske>(&datei,ow,"_corundobjektgasmaske","cogasmaske");
                                                                speichernobjekt<_corundobjektschutzhelm>(&datei,ow,"_corundobjektschutzhelm","coschutzh");
                                                                speichernobjekt<_corundobjektspritze>(&datei,ow,"_corundobjektspritze","cospritze");                                                                   
                                                                //--------------------------BÖDEN--------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Böden werden speicherbar gemacht ...");
                                                                speichernboden<_corundbodennormal>(&datei,ow,"_corundbodennormal","cbn");
                                                                speichernboden<_corundbodenschalter>(&datei,ow,"_corundbodenschalter","cbs");
                                                                speichernboden<_corundbodeninvers>(&datei,ow,"_corundbodeninvers","cbinv");
                                                                speichernboden<_corundbodenweltraum>(&datei,ow,"_corundbodenweltraum","cball");
                                                                speichernboden<_corundbodeneis>(&datei,ow,"_corundbodeneis","cbeis");
                                                                speichernboden<_corundbodensand>(&datei,ow,"_corundbodensand","cbsand");
                                                                speichernboden<_corundbodenschnee>(&datei,ow,"_corundbodenschnee","cbschnee");
                                                                speichernboden<_corundbodenwiese>(&datei,ow,"_corundbodenwiese","cbwiese");
                                                                speichernboden<_corundbodenwasser>(&datei,ow,"_corundbodenwasser","cbwasser");
                                                                speichernboden<_corundbodensumpf>(&datei,ow,"_corundbodensumpf","cbsumpf");
                                                                speichernboden<_corundbodenlava>(&datei,ow,"_corundbodenlava","cblava");
                                                                speichernboden<_corundbodenbeschleunigung>(&datei,ow,"_corundbodenbeschleunigung","cbbeschl");
                                                                speichernboden<_corundbodengradienz>(&datei,ow,"_corundbodengradienz","cbgrad");
                                                                speichernboden<_corundbodentransport>(&datei,ow,"_corundbodentransport","cbtrans");
                                                                speichernboden<_corundbodentotenkopf>(&datei,ow,"_corundbodentotenkopf","cbtot"); 
                                                                //-----------------------CORUNDKUGEL--------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Kugeln werden speicherbar gemacht ...");
                                                                _corundkugel*kuit;
                                                                unsigned int ku=0;
                                                                _speicherbardynamisch<_corundkugel>*sdku;
                                                                _speicherbardynamisch<_material<_tg> >*sdkumaterial;
                                                                _speicherbardynamisch<_oberflaeche<_tg> >*sdkuoberflaeche;
                                                                if(ow->anfang(kuit))do{
                                                                 sdku=new _speicherbardynamisch<_corundkugel >(&datei,sdow,kuit);
                                                                 sdku->typ("_corundkugel");
                                                                 _itoa(ku++,s,16);
                                                                 sdku->name(_zeichenkette<char>("ok")+s);
                                                                 sdkumaterial=new _speicherbardynamisch<_material<_tg> >(&datei,sdku,kuit);
                                                                 sdkumaterial->typ("_material");
                                                                 sdkuoberflaeche=new _speicherbardynamisch<_oberflaeche<_tg> >(&datei,sdku,kuit);
                                                                 sdkuoberflaeche->typ("_oberflaeche");
                                                                }while(ow->naechstes(kuit));
                                                                //-----------------------CORUNDGUMMIBAND--------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Gummibänder werden speicherbar gemacht ...");
                                                                _corundgummiband*gbit;
                                                                unsigned int gb=0;
                                                                _speicherbardynamisch<_corundgummiband>*sdgb;
                                                                if(ow->anfang(gbit))do{
                                                                 sdgb=new _speicherbardynamisch<_corundgummiband >(&datei,sdow,gbit);
                                                                 sdgb->typ("_corundgummiband");
                                                                 _itoa(gb++,s,16);
                                                                 sdgb->name(_zeichenkette<char>("gband")+s);
                                                                }while(ow->naechstes(gbit));
                                                                //-----------------------CORUNDFEDER--------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Federn werden speicherbar gemacht ...");
                                                                _corundfeder*cfit;
                                                                unsigned int cfe=0;
                                                                _speicherbardynamisch<_corundfeder>*sdcf;
                                                                if(ow->anfang(cfit))do{
                                                                 sdcf=new _speicherbardynamisch<_corundfeder>(&datei,sdow,cfit);
                                                                 sdcf->typ("_corundfeder");
                                                                 _itoa(cfe++,s,16);
                                                                 sdcf->name(_zeichenkette<char>("feder")+s);
                                                                }while(ow->naechstes(cfit));
                                                                //----------------------------------------------------------------------------
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Weltnetze werden speicherbar gemacht ...");
                                                                sdworld=new _speicherbardynamisch<_welt >(&datei,sdow,w);
                                                                sdworld->typ(worldtype);
                                                                sdworld->name(worldname+"0");
                                                                _speicherbardynamisch<_material<_tg> >*sdwmaterial;
                                                                sdwmaterial=new _speicherbardynamisch<_material<_tg> >(&datei,sdworld,w);
                                                                sdwmaterial->typ("_material");
                                                                mi=0;
                                                                
                                                                if(w->anfang(netz))do{
                                                                 if((netz->markierung()==1)&&(netz->nichtspeichern()==false)){
                                                                  _itoa(mi,s,16);
                                                                  speichernnetz<_welt>(&datei,ow,netz,sdworld,meshname+s);
                                                                  netz->markierung(0);
                                                                  mi++;
                                                                 };
                                                                }while(w->naechstes(netz));
                                                                

                                                                ti=0;
                                                                if(w->anfang(textur))do{
                                                                 sdtexture=new _speicherbardynamisch<_textur<_tb> >(&datei,sdworld,textur);
                                                                 sdtexture->typ(texturetype);_itoa(ti,s,16);
                                                                 sdtexture->name(texturename+s);
                                                                 
                                                                 _listenknoten<_bild<_tb> >*lnbild;
                                                                 if(textur->bitmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->bitmap()->naechstes(lnbild));
                                                                 if(textur->lightmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->lightmap()->naechstes(lnbild));
                                                                 if(textur->shadowmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->shadowmap()->naechstes(lnbild));
                                                                 if(textur->bumpmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->bumpmap()->naechstes(lnbild));
                                                                 if(textur->translightmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->translightmap()->naechstes(lnbild));
                                                                 if(textur->specularmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->specularmap()->naechstes(lnbild));
                                                                 if(textur->detailmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->detailmap()->naechstes(lnbild));
                                                                 if(textur->maskmap()->anfang(lnbild))do{
                                                                  bild=lnbild->objekt();
                                                                  sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,bild);
                                                                  sdmap->typ(bild->typ());
                                                                 }while(textur->maskmap()->naechstes(lnbild));
                                                                 
                                                                 ti++;
                                                                }while(w->naechstes(textur));
                                                                
                                                                li=0;
                                                                if(w->anfang(light))do{
                                                                 _corundlicht*clit;
                                                                 clit=dynamic_cast<_corundlicht*>(light);
                                                                 if(clit){
                                                                  _speicherbardynamisch<_corundlicht>*sdclight;
                                                                  sdclight=new _speicherbardynamisch<_corundlicht>(&datei,sdow,clit);
                                                                  sdclight->typ(clighttype);_itoa(li,s,16);
                                                                  sdclight->name(clightname+s);
                                                                  sdclight->holennamenqualifikation(clit->dateiqualifikation);
                                                                  sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdclight,light);
                                                                  sdlight->typ(lighttype);
                                                                  sdlight->name(lightname+s);
                                                                 }else{
                                                                  sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdworld,light);
                                                                  sdlight->typ(lighttype);_itoa(li,s,16);
                                                                  sdlight->name(lightname+s);
                                                                 };
                                                                 li++;
                                                                }while(w->naechstes(light));
                                                                
                                                                gi=0;
                                                                if(w->anfang(gravitation))do{
                                                                 sdgravitation=new _speicherbardynamisch<_gravitation<_tg> >(&datei,sdworld,gravitation);
                                                                 sdgravitation->typ(gravitationtype);_itoa(gi,s,16);
                                                                 sdgravitation->name(gravitationname+s);
                                                                 _speicherbardynamisch<_feld<_tg> >*sdfeld;
                                                                 sdfeld=new _speicherbardynamisch<_feld<_tg> >(&datei,sdgravitation,gravitation);
                                                                 sdfeld->typ("_feld");
                                                                 gi++;
                                                                }while(w->naechstes(gravitation));
                                                                
                                                                gi=0;
                                                                if(w->anfang(efeld))do{
                                                                 _speicherbardynamisch<_feldelektrostatisch<_tg> >*sdefeld;
                                                                 sdefeld=new _speicherbardynamisch<_feldelektrostatisch<_tg> >(&datei,sdworld,efeld);
                                                                 sdefeld->typ("_efeld");_itoa(gi,s,16);
                                                                 sdefeld->name(efeldname+s);
                                                                 _speicherbardynamisch<_feld<_tg> >*sdfeld;
                                                                 sdfeld=new _speicherbardynamisch<_feld<_tg> >(&datei,sdefeld,efeld);
                                                                 sdfeld->typ("_feld");
                                                                 gi++;
                                                                }while(w->naechstes(efeld));
                                                                
                                                                gi=0;
                                                                if(w->anfang(bfeld))do{
                                                                 _speicherbardynamisch<_feldmagnetostatisch<_tg> >*sdbfeld;
                                                                 sdbfeld=new _speicherbardynamisch<_feldmagnetostatisch<_tg> >(&datei,sdworld,bfeld);
                                                                 sdbfeld->typ("_bfeld");_itoa(gi,s,16);
                                                                 sdbfeld->name(bfeldname+s);
                                                                 _speicherbardynamisch<_feld<_tg> >*sdfeld;
                                                                 sdfeld=new _speicherbardynamisch<_feld<_tg> >(&datei,sdbfeld,bfeld);
                                                                 sdfeld->typ("_feld");
                                                                 gi++;
                                                                }while(w->naechstes(bfeld));
                                                                
                                                                pqi=0;
                                                                _partikelquelle*pqit;
                                                                if(w->anfang(pqit))do{
                                                                 partikelquellesprite=dynamic_cast<_partikelquellesprite*>(pqit);
                                                                 if(partikelquellesprite){
                                                                  sdpartikelquellesprite=new _speicherbardynamisch<_partikelquellesprite >(&datei,sdworld,partikelquellesprite);
                                                                  sdpartikelquellesprite->typ(partikelquellespritetype);_itoa(pqi,s,16);
                                                                  sdpartikelquellesprite->name(partikelquellespritename+s);
                                                                  _speicherbardynamisch<_partikelquelle>*sdpq;
                                                                  sdpq=new _speicherbardynamisch<_partikelquelle >(&datei,sdpartikelquellesprite,pqit);
                                                                  sdpq->typ("_partikelquelle");
                                                                  pqi++;
                                                                 };
                                                                }while(w->naechstes(pqit));
                                                                
                                                                cami=0;
                                                                if(w->anfang(camera))do{
                                                                 if(ow->kamera->kam!=camera){
                                                                  sdcamera=new _speicherbardynamisch<_kamera<_tg> >(&datei,sdworld,camera);
                                                                  sdcamera->typ(cameratype);_itoa(cami,s,16);
                                                                  sdcamera->name(cameraname+s);
                                                                  cami++;
                                                                 };
                                                                }while(w->naechstes(camera));
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Zonen werden speicherbar gemacht ...");
                                                                
                                                                zi=0;
                                                                if(w->anfang(zone))do{
                                                                 sdzone=new _speicherbardynamisch<_partition::_zone >(&datei,sdworld,zone);
                                                                 sdzone->typ(zonetype);_itoa(zi,s,16);
                                                                 sdzone->name(zonename+s);
                                                                 si=0;
                                                                 if(zone->anfang(sektor))do{
                                                                  sdsector=new _speicherbardynamisch<_partition::_sektor >(&datei,sdzone,sektor);
                                                                  sdsector->typ(sectortype);_itoa(si,s,16);
                                                                  sdsector->name(sectorname+s);
                                                                  
                                                                  if(sektor->anfang(light))do{
                                                                  
                                                                   _corundlicht*clit;
                                                                   clit=dynamic_cast<_corundlicht*>(light);
                                                                   if(clit){
                                                                    _speicherbardynamisch<_corundlicht>*sdclight;
                                                                    sdclight=new _speicherbardynamisch<_corundlicht>(&datei,sdsector,clit);
                                                                    sdclight->typ(clighttype);_itoa(li,s,16);
                                                                    sdclight->name(clightname+s);
                                                                    sdclight->holennamenqualifikation(clit->dateiqualifikation);
                                                                    sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdclight,light);
                                                                    sdlight->typ(lighttype);
                                                                    sdlight->name(lightname+s);
                                                                   }else{
                                                                    sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdsector,light);
                                                                    sdlight->typ(lighttype);_itoa(li,s,16);
                                                                    sdlight->name(lightname+s);
                                                                   };
                                                                   li++;
                                                                  }while(sektor->naechstes(light));
                                                                  
                                                                  ppi=0;
                                                                  if(sektor->anfang(ppolygon))do{
                                                                   sdppolygon=new _speicherbardynamisch<_partition::_polygon >(&datei,sdsector,ppolygon);
                                                                   sdppolygon->typ(ppolygontype);_itoa(ppi,s,16);
                                                                   sdppolygon->name(ppolygonname+s);
                                                                   pvi=0;
                                                                   if(ppolygon->anfang(pvertex))do{
                                                                    sdpvertex=new _speicherbardynamisch<_partition::_vertex >(&datei,sdppolygon,pvertex);
                                                                    sdpvertex->typ(pvertextype);_itoa(pvi,s,16);
                                                                    sdpvertex->name(pvertexname+s);
                                                                    pvi++;
                                                                   }while(ppolygon->naechstes(pvertex));
                                                                   ppi++;
                                                                  }while(sektor->naechstes(ppolygon));
                                                                  si++;
                                                                 }while(zone->naechstes(sektor));
                                                                 pli=0;
                                                                 if(zone->anfang(ebene))do{
                                                                  sdplane=new _speicherbardynamisch<_partition::_ebene >(&datei,sdzone,ebene);
                                                                  sdplane->typ(planetype);_itoa(pli,s,16);
                                                                  sdplane->name(planename+s);
                                                                  pli++;
                                                                 }while(zone->naechstes(ebene));
                                                                 zi++;
                                                                }while(w->naechstes(zone));
                                                                hf->statusbar->text(2,L"Szene wird gespeichert : Speicherstruktur wird geschrieben ...");
                                                                datei.speichern();
                                                                hf->statusbar->text(2,L"Speichern der Szene beendet.");


};
template<class T>void ladennetz(_dateispeicherbartext*datei,_corundwelt*ow,_speicherbardynamisch<T>*sd,_dateispeicherbarknoten*meshnit,_netz*mesh,const _zeichenkette<char>&typ){
                                                                _material<_tg>* mat;
                                                                _oberflaeche<_tg>*ober;
                                                                _polygon*polygon;
                                                                _vertex*vertex;
                                                                _verbindervertexpolygon*connector;
                                                                _speicherbardynamisch<_netz >*sdmesh;
                                                                _speicherbardynamisch<_polygon >*sdpolygon;
                                                                _speicherbardynamisch<_vertex >*sdvertex;
                                                                _vektor3<_tg> nullvector;
                                                                _dateispeicherbarknoten*mkit; 
                                                                _dateispeicherbarknoten*kit;
                                                                //-------------------------------------------------
                                                                sdmesh=new _speicherbardynamisch<_netz>(datei,sd,mesh);
                                                                mesh->laden(meshnit,sdmesh);
                                                                
                                                                
                                                                if(meshnit->anfang(mkit))do{
                                                                 if(mkit->typ()=="_polygon"){
                                                                  polygon=new _polygon(mesh);
                                                                  sdpolygon=new _speicherbardynamisch<_polygon >(datei,sdmesh,polygon);
                                                                  polygon->laden(mkit,sdpolygon);
                                                                  if(mkit->anfang(kit))do{
                                                                   if(kit->typ()=="_oberflaeche"){
                                                                    ober=polygon;
                                                                    ober->laden(kit,new _speicherbardynamisch<_oberflaeche<_tg> >(datei,sdpolygon,ober));
                                                                   };
                                                                  }while(mkit->naechstes(kit));
                                                                  
                                                                  
                                                                  
                                                                  if(mkit->anfang(kit))do{
                                                                   if(kit->typ()=="_verbinder"){
                                                                    connector=new _verbindervertexpolygon(0,polygon);//pseudo parameter, spätere reassoziation
                                                                    connector->laden(kit,new _speicherbardynamisch<_verbindervertexpolygon >(datei,sdpolygon,connector));
                                                                   };
                                                                  }while(mkit->naechstes(kit));
                                                                  
                                                                  
                                                                 }else if(mkit->typ()=="_vertex"){
                                                                  vertex=new _vertex(mesh,nullvector);//pseudo parameter, spätere reassoziation
                                                                  sdvertex=new _speicherbardynamisch<_vertex >(datei,sdmesh,vertex);
                                                                  vertex->laden(mkit,sdvertex);
                                                                  
                                                                 /* if(mkit->anfang(kit))do{
                                                                   if(kit->typ()=="_verbinder"){
                                                                    connector=new _verbindervertexpolygon(vertex,0);//pseudo parameter, spätere reassoziation
                                                                    connector->laden(kit,new _speicherbardynamisch<_verbindervertexpolygon >(datei,sdvertex,connector));
                                                                   };
                                                                  }while(mkit->naechstes(kit));
                                                                  */
                                                                  
                                                                 }else if(mkit->typ()=="_material"){
                                                                  mat=mesh;
                                                                  mat->laden(mkit,new _speicherbardynamisch<_material<_tg> >(datei,sdmesh,mat));
                                                                 };
                                                                }while(meshnit->naechstes(mkit));

};
template<class T>void ladenstein(_dateispeicherbartext*datei,_corundwelt*ow,_speicherbardynamisch<_corundwelt>*sdow,const _zeichenkette<char>&typ){
                                                                _liste<_dateispeicherbarknoten > nodes;
                                                                _listenknoten<_dateispeicherbarknoten >*nit;
                                                                _speicherbardynamisch<T>*sd;
                                                                _liste<_dateispeicherbarknoten > osnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*osit;
                                                                _speicherbardynamisch<_corundstein>*sdos;
                                                                _liste<_dateispeicherbarknoten > nenodes;
                                                                //_listenknoten<_dateispeicherbarknoten >*neit;
                                                                _zeichenkette<char> volltyp;
                                                                //-----------------------------------------
                                                                datei->holenuebertyp(typ,nodes);
                                                                if(nodes.anfang(nit))do{
                                                                 T*ns=new T(ow);
                                                                 nit->objekt()->holennamenqualifikation(ns->dateiqualifikation);
                                                                 sd=new _speicherbardynamisch<T>(datei,sdow,ns);
                                                                 ns->laden(nit->objekt(),sd);
                                                                 _corundstein*os;
                                                                 os=ns;
                                                                 osnodes.aushaengen();
                                                                 //volltyp="";
                                                                 volltyp=typ;
                                                                 volltyp+="::_corundstein";
                                                                 nit->objekt()->holenuebertyp(volltyp,osnodes);
                                                                 if(osnodes.anfang(osit)){
                                                                  
                                                                  sdos=new _speicherbardynamisch<_corundstein>(datei,sd,os);
                                                                  os->laden(osit->objekt(),sdos);
                                                                  _listenknoten<_dateispeicherbarknoten >*neit;
                                                                  nenodes.aushaengen();
                                                                  osit->objekt()->holenuebertyp(volltyp+"::_netz",nenodes);
                                                                  if(nenodes.anfang(neit)){
                                                                  
                                                                   _netz*ne=os;
                                                                   ne->einhaengen(ow->welt);
                                                                   ladennetz<_corundstein>(datei,ow,sdos,neit->objekt(),ne,volltyp+"::_netz");
                                                                  };
                                                                 };
                                                                }while(nodes.naechstes(nit));
};
void ladenstein(_dateispeicherbartext*datei,_corundwelt*ow,_speicherbardynamisch<_corundwelt>*sdow){
                                                                _liste<_dateispeicherbarknoten > nodes;
                                                                _listenknoten<_dateispeicherbarknoten >*nit;
                                                                _speicherbardynamisch<_corundstein>*sdos;
                                                                _liste<_dateispeicherbarknoten > nenodes;
                                                                _zeichenkette<char> typ="_corundwelt::_corundstein";
                                                                //-----------------------------------------
                                                                datei->holenuebertyp(typ,nodes);
                                                                if(nodes.anfang(nit))do{
                                                                 _corundstein*os=new _corundstein(ow);
                                                                  sdos=new _speicherbardynamisch<_corundstein>(datei,sdow,os);
                                                                  os->laden(nit->objekt(),sdos);
                                                                  _dateispeicherbarknoten*netzknoten;
                                                                  if(nit->objekt()->anfang(netzknoten)){
                                                                   _netz*ne=os;
                                                                   ne->einhaengen(ow->welt);
                                                                   ladennetz<_corundstein>(datei,ow,sdos,netzknoten,ne,typ+"::_netz");
                                                                  };
                                                                }while(nodes.naechstes(nit));
};
template<class T>void ladenobjekt(_dateispeicherbartext*datei,_corundwelt*ow,_speicherbardynamisch<_corundwelt>*sdow,const _zeichenkette<char>&typ){
                                                                _liste<_dateispeicherbarknoten > nodes;
                                                                _listenknoten<_dateispeicherbarknoten >*nit;
                                                                _speicherbardynamisch<T>*sd;
                                                                _liste<_dateispeicherbarknoten > osnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*osit;
                                                                _speicherbardynamisch<_corundobjekt>*sdos;
                                                                _liste<_dateispeicherbarknoten > nenodes;
                                                                //_listenknoten<_dateispeicherbarknoten >*neit;
                                                                _zeichenkette<char> volltyp;
                                                                //-----------------------------------------
                                                                datei->holenuebertyp(typ,nodes);
                                                                if(nodes.anfang(nit))do{
                                                                 T*ns=new T(ow,_vektor3<_tg>(0,0,0));
                                                                 nit->objekt()->holennamenqualifikation(ns->dateiqualifikation);
                                                                 sd=new _speicherbardynamisch<T>(datei,sdow,ns);
                                                                 ns->laden(nit->objekt(),sd);
                                                                 _corundobjekt*os;
                                                                 os=ns;
                                                                 osnodes.aushaengen();
                                                                 //volltyp="";
                                                                 volltyp=typ;
                                                                 volltyp+="::_corundobjekt";
                                                                 nit->objekt()->holenuebertyp(volltyp,osnodes);
                                                                 if(osnodes.anfang(osit)){
                                                                  
                                                                  sdos=new _speicherbardynamisch<_corundobjekt>(datei,sd,os);
                                                                  os->laden(osit->objekt(),sdos);
                                                                 };
                                                                }while(nodes.naechstes(nit));
};
template<class T>void ladenboden(_dateispeicherbartext*datei,_corundwelt*ow,_speicherbardynamisch<_corundwelt>*sdow,const _zeichenkette<char>&typ){
                                                                _liste<_dateispeicherbarknoten > nodes;
                                                                _listenknoten<_dateispeicherbarknoten >*nit;
                                                                _speicherbardynamisch<T>*sd;
                                                                _liste<_dateispeicherbarknoten > cbnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*cbit;
                                                                _speicherbardynamisch<_corundboden>*sdcb;
                                                                _liste<_dateispeicherbarknoten > nenodes;
                                                                //_listenknoten<_dateispeicherbarknoten >*neit;
                                                                _zeichenkette<char> volltyp;
                                                                //-----------------------------------------
                                                                datei->holenuebertyp(typ,nodes);
                                                                if(nodes.anfang(nit))do{
                                                                 T*nb=new T(ow,_vektor3<_tg>(0,0,0),_vektor3<_tg>(1,0,0),_vektor3<_tg>(0,0,1));
                                                                 nit->objekt()->holennamenqualifikation(nb->dateiqualifikation);
                                                                 sd=new _speicherbardynamisch<T>(datei,sdow,nb);
                                                                 nb->laden(nit->objekt(),sd);
                                                                 _corundboden*cb;
                                                                 cb=nb;
                                                                 cbnodes.aushaengen();
                                                                 //volltyp="";
                                                                 volltyp=typ;
                                                                 volltyp+="::_corundboden";
                                                                 nit->objekt()->holenuebertyp(volltyp,cbnodes);
                                                                 if(cbnodes.anfang(cbit)){
                                                                  
                                                                  sdcb=new _speicherbardynamisch<_corundboden>(datei,sd,cb);
                                                                  cb->laden(cbit->objekt(),sdcb);
                                                                  _listenknoten<_dateispeicherbarknoten >*neit;
                                                                  nenodes.aushaengen();
                                                                  cbit->objekt()->holenuebertyp(volltyp+"::_netz",nenodes);
                                                                  if(nenodes.anfang(neit)){
                                                                  
                                                                   _netz*ne=cb;
                                                                   ne->einhaengen(ow->welt);
                                                                   ladennetz<_corundboden>(datei,ow,sdcb,neit->objekt(),ne,volltyp+"::_netz");
                                                                   
                                                                  };
                                                                 };
                                                                }while(nodes.naechstes(nit));
};
void corundweltladen(_hauptfenster*hf,_zeichenkette<char> fn,_corundwelt*&ow,_grafik*grafik,_akustik*sound){
                                                                _vektor3<_tg> nullvector;
                                                                _vektor3<_tg> hvg;
                                                                _vektor4<_to> hvo;
                                                                _vektor3<_to> hvo3;
                                                                _welt*welt;
                                                                _netz*netz;
                                                                _licht<_tg,_to>*light;
                                                                _corundlicht*clight;
                                                                _gravitation<_tg>*gravitation;
                                                                _feldelektrostatisch<_tg>*efeld;
                                                                _feldmagnetostatisch<_tg>*bfeld;
                                                                _partikelquellesprite*partikelquellesprite;
                                                                _kamera<_tg>*camera;
                                                                _partition::_zone*zone;
                                                                _partition::_ebene*ebene;
                                                                _partition::_sektor*sektor;
                                                                _partition::_polygon*ppolygon;
                                                                _partition::_vertex*pvertex;
                                                                _liste<_dateispeicherbarknoten > ownodes;
                                                                _listenknoten<_dateispeicherbarknoten >*ownit;
                                                                _liste<_dateispeicherbarknoten > worldnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*worldnit;
                                                                _liste<_dateispeicherbarknoten > meshnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*meshnit;
                                                                _liste<_dateispeicherbarknoten > lightnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*lightnit;
                                                                _liste<_dateispeicherbarknoten > clightnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*clightnit;
                                                                _liste<_dateispeicherbarknoten > gravitationnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*gravitationnit;
                                                                _liste<_dateispeicherbarknoten > efeldnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*efeldnit;
                                                                _liste<_dateispeicherbarknoten > bfeldnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*bfeldnit;
                                                                _liste<_dateispeicherbarknoten > partikelquellespritenodes;
                                                                _listenknoten<_dateispeicherbarknoten >*partikelquellespritenit;
                                                                _liste<_dateispeicherbarknoten > cameranodes;
                                                                _listenknoten<_dateispeicherbarknoten >*cameranit;
                                                                _liste<_dateispeicherbarknoten > zonenodes;
                                                                _listenknoten<_dateispeicherbarknoten >*zonenit;
                                                                _liste<_dateispeicherbarknoten > planenodes;
                                                                _listenknoten<_dateispeicherbarknoten >*planenit;
                                                                _liste<_dateispeicherbarknoten > sectornodes;
                                                                _listenknoten<_dateispeicherbarknoten >*sectornit;
                                                                _liste<_dateispeicherbarknoten > ppolygonnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*ppolygonnit;
                                                                _liste<_dateispeicherbarknoten > pvertexnodes;
                                                                _listenknoten<_dateispeicherbarknoten >*pvertexnit;
                                                                _speicherbardynamisch<_corundwelt >*sdow;
                                                                _speicherbardynamisch<_welt >*sdworld;
                                                                _speicherbardynamisch<_licht<_tg,_to> >*sdlight;
                                                                _speicherbardynamisch<_corundlicht>*sdclight;
                                                                _speicherbardynamisch<_gravitation<_tg> >*sdgravitation;
                                                                _speicherbardynamisch<_feldelektrostatisch<_tg> >*sdefeld;
                                                                _speicherbardynamisch<_feldmagnetostatisch<_tg> >*sdbfeld;
                                                                _speicherbardynamisch<_partikelquellesprite >*sdpartikelquellesprite;
                                                                _speicherbardynamisch<_kamera<_tg> >*sdcamera;
                                                                _speicherbardynamisch<_partition::_zone >*sdzone;
                                                                _speicherbardynamisch<_partition::_ebene >*sdplane;
                                                                _speicherbardynamisch<_partition::_sektor >*sdsector;
                                                                _speicherbardynamisch<_partition::_polygon >*sdppolygon;
                                                                _speicherbardynamisch<_partition::_vertex >*sdpvertex;
                                                                _zeichenkette<char> owtype="_corundwelt";
                                                                _zeichenkette<char> worldtype="_corundwelt::_welt";
                                                                _zeichenkette<char> meshtype="_netz";
                                                                _zeichenkette<char> polygontype="_polygon";
                                                                _zeichenkette<char> vertextype="_vertex";
                                                                _zeichenkette<char> connectortype="_verbinder";
                                                                _zeichenkette<char> texturevectortype="_texturvektor";
                                                                _zeichenkette<char> texturetype="_textur";
                                                                _zeichenkette<char> maptgatype="_bild";
                                                                _zeichenkette<char> lighttype="_licht";
                                                                _zeichenkette<char> clighttype="_clicht";
                                                                _zeichenkette<char> gravitationtype="_gravitation";
                                                                _zeichenkette<char> efeldtype="_efeld";
                                                                _zeichenkette<char> bfeldtype="_bfeld";
                                                                _zeichenkette<char> partikelquellespritetype="_partikelquellesprite";
                                                                _zeichenkette<char> cameratype="_kamera";
                                                                _zeichenkette<char> zonetype="_zone";
                                                                _zeichenkette<char> planetype="_ebene";
                                                                _zeichenkette<char> sectortype="_sektor";
                                                                _zeichenkette<char> ppolygontype="_partitionpolygon";
                                                                _zeichenkette<char> pvertextype="_partitionvertex";
                                                                //_win::_zeit tt;
                                                                //tt.anfang();
                                                                //unsigned int t0;
                                                                //unsigned int t1;
                                                                //unsigned int t2;
                                                                //---------------------------
                                                                hf->statusbar->text(2,L"Szene wird geladen : Dateiknoten werden angelegt ...");
                                                                _dateispeicherbartext datei(fn);
                                                                hf->statusbar->text(2,L"Szene wird geladen : corundwelt wird konstruiert ...");
                                                                //t0=tt.system();
                                                                ow=new _corundwelt(grafik,*hf->texturverwaltung,sound,*hf->tonverwaltung);
                                                                hf->statusbar->text(2,L"Szene wird geladen : Steine werden geladen...");

                                                                welt=ow->welt;
                                                                datei.holenuebertyp("_corundwelt",ownodes);
                                                                if(ownodes.anfang(ownit)){
                                                                 sdow=new _speicherbardynamisch<_corundwelt>(&datei,ow);
                                                                 ow->laden(ownit->objekt(),sdow);
                                                                 
                                                                 
                                                                 _corundknoten*knoten;
                                                                 _liste<_dateispeicherbarknoten > knotennodes;
                                                                 _listenknoten<_dateispeicherbarknoten >*knotennit;
                                                                 _speicherbardynamisch<_corundknoten>*sdknoten;
                                                                 knotennodes.aushaengen();
                                                                 datei.holenuebertyp("_corundwelt::_corundknoten",knotennodes);
                                                                 if(knotennodes.anfang(knotennit))do{
                                                                  knoten=new _corundknoten(ow,_vektor3<_tg>(0,0,0),0);
                                                                  sdknoten=new _speicherbardynamisch<_corundknoten>(&datei,sdow,knoten);
                                                                  knoten->laden(knotennit->objekt(),sdknoten);
                                                                 }while(knotennodes.naechstes(knotennit));
                                                                 
                                                                 
                                                                 ladenstein<_corundsteincorund>(&datei,ow,sdow,"_corundwelt::_corundsteincorund");
                                                                 ladenstein<_corundsteingummiband>(&datei,ow,sdow,"_corundwelt::_corundsteingummiband");
                                                                 ladenstein<_corundsteinschere>(&datei,ow,sdow,"_corundwelt::_corundsteinschere");
                                                                 ladenstein<_corundsteinschieb>(&datei,ow,sdow,"_corundwelt::_corundsteinschieb");
                                                                 ladenstein<_corundsteinboulder>(&datei,ow,sdow,"_corundwelt::_corundsteinboulder");
                                                                 ladenstein<_corundsteinrotation>(&datei,ow,sdow,"_corundwelt::_corundsteinrotation");
                                                                 ladenstein<_corundsteinimpuls>(&datei,ow,sdow,"_corundwelt::_corundsteinimpuls");
                                                                 ladenstein<_corundsteinelektrisch>(&datei,ow,sdow,"_corundwelt::_corundsteinelektrisch");
                                                                 ladenstein<_corundsteinerdung>(&datei,ow,sdow,"_corundwelt::_corundsteinerdung");
                                                                 ladenstein<_corundsteinbeschleunigung>(&datei,ow,sdow,"_corundwelt::_corundsteinbeschleunigung");
                                                                 ladenstein<_corundsteintotenkopf>(&datei,ow,sdow,"_corundwelt::_corundsteintotenkopf");
                                                                 ladenstein<_corundsteintor>(&datei,ow,sdow,"_corundwelt::_corundsteintor");
                                                                 ladenstein<_corundsteinschalter>(&datei,ow,sdow,"_corundwelt::_corundsteinschalter");
                                                                 ladenstein<_corundsteinkugelgen>(&datei,ow,sdow,"_corundwelt::_corundsteinkugelgen");
                                                                 ladenstein<_corundsteindach>(&datei,ow,sdow,"_corundwelt::_corundsteindach");
                                                                 ladenstein<_corundsteinflak>(&datei,ow,sdow,"_corundwelt::_corundsteinflak");
                                                                 ladenstein<_corundsteinausgang>(&datei,ow,sdow,"_corundwelt::_corundsteinausgang");
                                                                 ladenstein<_corundsteinsenker>(&datei,ow,sdow,"_corundwelt::_corundsteinsenker");
                                                                 ladenstein<_corundsteinlaser>(&datei,ow,sdow,"_corundwelt::_corundsteinlaser");
                                                                 ladenstein<_corundsteinspiegel>(&datei,ow,sdow,"_corundwelt::_corundsteinspiegel");
                                                                 ladenstein<_corundsteinschloss>(&datei,ow,sdow,"_corundwelt::_corundsteinschloss");
                                                                 ladenstein<_corundsteinereignis>(&datei,ow,sdow,"_corundwelt::_corundsteinereignis");
                                                                 ladenstein<_corundsteingerissen>(&datei,ow,sdow,"_corundwelt::_corundsteingerissen");
                                                                 ladenstein<_corundsteinspuck>(&datei,ow,sdow,"_corundwelt::_corundsteinspuck");
                                                                 ladenstein<_corundsteintauscher>(&datei,ow,sdow,"_corundwelt::_corundsteintauscher");
                                                                 ladenstein<_corundsteinmagnetisch>(&datei,ow,sdow,"_corundwelt::_corundsteinmagnetisch");
                                                                 ladenstein<_corundsteindieb>(&datei,ow,sdow,"_corundwelt::_corundsteindieb");
                                                                 ladenstein<_corundsteinfliegengen>(&datei,ow,sdow,"_corundwelt::_corundsteinfliegengen");
                                                                 ladenstein<_corundsteinspinnengen>(&datei,ow,sdow,"_corundwelt::_corundsteinspinnengen");
                                                                 ladenstein<_corundsteinshogun>(&datei,ow,sdow,"_corundwelt::_corundsteinshogun");
                                                                 ladenstein<_corundsteinpuzzle>(&datei,ow,sdow,"_corundwelt::_corundsteinpuzzle");
                                                                 ladenstein<_corundsteingas>(&datei,ow,sdow,"_corundwelt::_corundsteingas");
                                                                 ladenstein<_corundsteinkombinationsschloss>(&datei,ow,sdow,"_corundwelt::_corundsteinkombinationsschloss");
                                                                 ladenstein<_corundsteindrehkreuz>(&datei,ow,sdow,"_corundwelt::_corundsteindrehkreuz");                                                                  
                                                                 ladenstein<_corundsteineinbahn>(&datei,ow,sdow,"_corundwelt::_corundsteineinbahn");                                                                  
                                                                 ladenstein(&datei,ow,sdow);
                                                                 
                                                                 ladenobjekt<_corundobjektersatz>(&datei,ow,sdow,"_corundwelt::_corundobjektersatz");
                                                                 ladenobjekt<_corundobjektschluessela>(&datei,ow,sdow,"_corundwelt::_corundobjektschluessela");
                                                                 ladenobjekt<_corundobjektbombe>(&datei,ow,sdow,"_corundwelt::_corundobjektbombe");
                                                                 ladenobjekt<_corundobjektdynamit>(&datei,ow,sdow,"_corundwelt::_corundobjektdynamit");
                                                                 ladenobjekt<_corundobjektmine>(&datei,ow,sdow,"_corundwelt::_corundobjektmine");
                                                                 ladenobjekt<_corundobjektsteinpille>(&datei,ow,sdow,"_corundwelt::_corundobjektsteinpille");
                                                                 ladenobjekt<_corundobjektalkohol>(&datei,ow,sdow,"_corundwelt::_corundobjektalkohol");
                                                                 ladenobjekt<_corundobjektbungeeseil>(&datei,ow,sdow,"_corundwelt::_corundobjektbungeeseil");
                                                                 ladenobjekt<_corundobjektschere>(&datei,ow,sdow,"_corundwelt::_corundobjektschere");
                                                                 ladenobjekt<_corundobjektzettel>(&datei,ow,sdow,"_corundwelt::_corundobjektzettel");
                                                                 ladenobjekt<_corundobjektfallschirm>(&datei,ow,sdow,"_corundwelt::_corundobjektfallschirm");
                                                                 ladenobjekt<_corundobjektzauberstab>(&datei,ow,sdow,"_corundwelt::_corundobjektzauberstab");
                                                                 ladenobjekt<_corundobjekttriebwerk>(&datei,ow,sdow,"_corundwelt::_corundobjekttriebwerk");
                                                                 ladenobjekt<_corundobjektgesundheit>(&datei,ow,sdow,"_corundwelt::_corundobjektgesundheit");
                                                                 ladenobjekt<_corundobjektreisszwecke>(&datei,ow,sdow,"_corundwelt::_corundobjektreisszwecke");
                                                                 ladenobjekt<_corundobjekthammer>(&datei,ow,sdow,"_corundwelt::_corundobjekthammer");
                                                                 ladenobjekt<_corundobjektgasbrenner>(&datei,ow,sdow,"_corundwelt::_corundobjektgasbrenner");
                                                                 ladenobjekt<_corundobjektschutzschild>(&datei,ow,sdow,"_corundwelt::_corundobjektschutzschild");
                                                                 ladenobjekt<_corundobjektschneidbrenner>(&datei,ow,sdow,"_corundwelt::_corundobjektschneidbrenner"); 
                                                                 ladenobjekt<_corundobjektschwarzesloch>(&datei,ow,sdow,"_corundwelt::_corundobjektschwarzesloch");
                                                                 ladenobjekt<_corundobjektmagnet>(&datei,ow,sdow,"_corundwelt::_corundobjektmagnet");
                                                                 ladenobjekt<_corundobjektpresslufthammer>(&datei,ow,sdow,"_corundwelt::_corundobjektpresslufthammer");
                                                                 ladenobjekt<_corundobjektteleporter>(&datei,ow,sdow,"_corundwelt::_corundobjektteleporter");
                                                                 ladenobjekt<_corundobjektgleitmittel>(&datei,ow,sdow,"_corundwelt::_corundobjektgleitmittel");
                                                                 ladenobjekt<_corundobjektgeld>(&datei,ow,sdow,"_corundwelt::_corundobjektgeld");
                                                                 ladenobjekt<_corundobjektsprungfeder>(&datei,ow,sdow,"_corundwelt::_corundobjektsprungfeder");
                                                                 ladenobjekt<_corundobjektskalierer>(&datei,ow,sdow,"_corundwelt::_corundobjektskalierer");
                                                                 ladenobjekt<_corundobjektpflanze>(&datei,ow,sdow,"_corundwelt::_corundobjektpflanze");
                                                                 ladenobjekt<_corundobjektobst>(&datei,ow,sdow,"_corundwelt::_corundobjektobst");
                                                                 ladenobjekt<_corundobjektdematerialisierung>(&datei,ow,sdow,"_corundwelt::_corundobjektdematerialisierung");
                                                                 ladenobjekt<_corundobjektdevisualisierung>(&datei,ow,sdow,"_corundwelt::_corundobjektdevisualisierung");
                                                                 ladenobjekt<_corundobjektinsektenspray>(&datei,ow,sdow,"_corundwelt::_corundobjektinsektenspray");
                                                                 ladenobjekt<_corundobjektfeuerloescher>(&datei,ow,sdow,"_corundwelt::_corundobjektfeuerloescher");
                                                                 ladenobjekt<_corundobjektsummer>(&datei,ow,sdow,"_corundwelt::_corundobjektsummer");
                                                                 ladenobjekt<_corundobjektblinker>(&datei,ow,sdow,"_corundwelt::_corundobjektblinker");
                                                                 ladenobjekt<_corundobjektbatterie>(&datei,ow,sdow,"_corundwelt::_corundobjektbatterie");
                                                                 ladenobjekt<_corundobjektpinsel>(&datei,ow,sdow,"_corundwelt::_corundobjektpinsel");
                                                                 ladenobjekt<_corundobjektbesen>(&datei,ow,sdow,"_corundwelt::_corundobjektbesen");
                                                                 ladenobjekt<_corundobjektlampe>(&datei,ow,sdow,"_corundwelt::_corundobjektlampe");
                                                                 ladenobjekt<_corundobjektkerze>(&datei,ow,sdow,"_corundwelt::_corundobjektkerze");
                                                                 ladenobjekt<_corundobjektgewicht>(&datei,ow,sdow,"_corundwelt::_corundobjektgewicht");
                                                                 ladenobjekt<_corundobjektgasmaske>(&datei,ow,sdow,"_corundwelt::_corundobjektgasmaske");
                                                                 ladenobjekt<_corundobjektschutzhelm>(&datei,ow,sdow,"_corundwelt::_corundobjektschutzhelm");
                                                                 ladenobjekt<_corundobjektspritze>(&datei,ow,sdow,"_corundwelt::_corundobjektspritze"); 
 
                                                                 ladenboden<_corundbodennormal>(&datei,ow,sdow,"_corundwelt::_corundbodennormal");
                                                                 ladenboden<_corundbodenschalter>(&datei,ow,sdow,"_corundwelt::_corundbodenschalter");
                                                                 ladenboden<_corundbodeninvers>(&datei,ow,sdow,"_corundwelt::_corundbodeninvers");
                                                                 ladenboden<_corundbodenweltraum>(&datei,ow,sdow,"_corundwelt::_corundbodenweltraum");
                                                                 ladenboden<_corundbodeneis>(&datei,ow,sdow,"_corundwelt::_corundbodeneis");
                                                                 ladenboden<_corundbodensand>(&datei,ow,sdow,"_corundwelt::_corundbodensand");
                                                                 ladenboden<_corundbodenschnee>(&datei,ow,sdow,"_corundwelt::_corundbodenschnee");
                                                                 ladenboden<_corundbodenwiese>(&datei,ow,sdow,"_corundwelt::_corundbodenwiese");
                                                                 ladenboden<_corundbodenwasser>(&datei,ow,sdow,"_corundwelt::_corundbodenwasser");
                                                                 ladenboden<_corundbodensumpf>(&datei,ow,sdow,"_corundwelt::_corundbodensumpf");
                                                                 ladenboden<_corundbodenlava>(&datei,ow,sdow,"_corundwelt::_corundbodenlava");
                                                                 ladenboden<_corundbodenbeschleunigung>(&datei,ow,sdow,"_corundwelt::_corundbodenbeschleunigung");
                                                                 ladenboden<_corundbodengradienz>(&datei,ow,sdow,"_corundwelt::_corundbodengradienz");
                                                                 ladenboden<_corundbodentransport>(&datei,ow,sdow,"_corundwelt::_corundbodentransport");
                                                                 ladenboden<_corundbodentotenkopf>(&datei,ow,sdow,"_corundwelt::_corundbodentotenkopf"); 
 
                                                                 hf->statusbar->text(2,L"Szene wird geladen : Kugeln werden geladen...");
                                                                 _liste<_dateispeicherbarknoten > kugelnodes;
                                                                 _listenknoten<_dateispeicherbarknoten >*kugelnit;
                                                                 _speicherbardynamisch<_corundkugel>*sdkugel;
                                                                 _dateispeicherbarknoten*kit;
                                                                 _corundkugel*kugel;
                                                                 _material<_tg>*mat;
                                                                 _oberflaeche<_tg>*obe;
                                                                 kugelnodes.aushaengen();
                                                                 datei.holenuebertyp("_corundwelt::_corundkugel",kugelnodes);
                                                                 if(kugelnodes.anfang(kugelnit))do{
                                                                  kugel=new _corundkugel(ow,_vektor3<_tg>(0,0,0),_vektor3<_tg>(0,0,0),1,_vektor4<_to>(1,1,1,1));
                                                                  kugelnit->objekt()->holennamenqualifikation(kugel->dateiqualifikation);
                                                                  sdkugel=new _speicherbardynamisch<_corundkugel>(&datei,sdow,kugel);
                                                                  kugel->laden(kugelnit->objekt(),sdkugel);
                                                                  if(kugelnit->objekt()->anfang(kit))do{
                                                                   if(kit->typ()=="_material"){
                                                                    mat=kugel;
                                                                    mat->laden(kit,new _speicherbardynamisch<_material<_tg> >(&datei,sdkugel,kugel));
                                                                   }else
                                                                   if(kit->typ()=="_oberflaeche"){
                                                                    obe=kugel;
                                                                    obe->laden(kit,new _speicherbardynamisch<_oberflaeche<_tg> >(&datei,sdkugel,kugel));
                                                                   };
                                                                  }while(kugelnit->objekt()->naechstes(kit));
                                                                 }while(kugelnodes.naechstes(kugelnit));
                                                                 
                                                                 hf->statusbar->text(2,L"Szene wird geladen : Gummibänder werden geladen...");
                                                                 _liste<_dateispeicherbarknoten > gumminodes;
                                                                 _listenknoten<_dateispeicherbarknoten >*gumminit;
                                                                 _speicherbardynamisch<_corundgummiband>*sdgummi;
                                                                 _corundgummiband*gummi;
                                                                 gumminodes.aushaengen();
                                                                 datei.holenuebertyp("_corundwelt::_corundgummiband",gumminodes);
                                                                 if(gumminodes.anfang(gumminit))do{
                                                                  gummi=new _corundgummiband(ow);
                                                                  //gumminit->objekt()->holennamenqualifikation(gummi->dateiqualifikation);
                                                                  sdgummi=new _speicherbardynamisch<_corundgummiband>(&datei,sdow,gummi);
                                                                  gummi->laden(gumminit->objekt(),sdgummi);
                                                                 }while(gumminodes.naechstes(gumminit));
                                                                 
                                                                 hf->statusbar->text(2,L"Szene wird geladen : Federn werden geladen...");
                                                                 _liste<_dateispeicherbarknoten > federnodes;
                                                                 _listenknoten<_dateispeicherbarknoten >*federnit;
                                                                 _speicherbardynamisch<_corundfeder>*sdfeder;
                                                                 _corundfeder*feder;
                                                                 federnodes.aushaengen();
                                                                 datei.holenuebertyp("_corundwelt::_corundfeder",federnodes);
                                                                 if(federnodes.anfang(federnit))do{
                                                                  feder=new _corundfeder(ow);
                                                                  //federnit->objekt()->holennamenqualifikation(feder->dateiqualifikation);
                                                                  sdfeder=new _speicherbardynamisch<_corundfeder>(&datei,sdow,feder);
                                                                  feder->laden(federnit->objekt(),sdfeder);
                                                                 }while(federnodes.naechstes(federnit));                                                                 
                                                                 
                                                                 hf->statusbar->text(2,L"Szene wird geladen : Corundlichter werden geladen...");
                                                                 clightnodes.aushaengen();
                                                                 datei.holenuebertyp("_corundwelt::_clicht",clightnodes);
                                                                 if(clightnodes.anfang(clightnit))do{
                                                                  hvo3.setzen(1,0,0);
                                                                  clight=new _corundlicht(ow,welt,nullvector,hvo3,10);
                                                                  clightnit->objekt()->holennamenqualifikation(clight->dateiqualifikation);
                                                                  sdclight=new _speicherbardynamisch<_corundlicht>(&datei,sdow,clight);
                                                                  clight->laden(clightnit->objekt(),sdclight);
                                                                  if(clightnit->objekt()->anfang(kit)){
                                                                  if(kit->typ()==lighttype){
                                                                   //clightnit->objekt()->holenuebertyp(owtype+"::"+clighttype+"::"+lighttype,lightnodes);
                                                                   //if(lightnodes.anfang(lightnit)){
                                                                   hvo3.setzen(1,0,0);
                                                                   light=clight;
                                                                   sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdclight,light);
                                                                   light->laden(kit,sdlight);
                                                                  };
                                                                  };
                                                                 }while(clightnodes.naechstes(clightnit));


                                                                 hf->statusbar->text(2,L"Szene wird geladen : Weltnetze werden geladen...");
                                                                 worldnodes.aushaengen();
                                                                 datei.holenuebertyp(worldtype,worldnodes);
                                                                 if(worldnodes.anfang(worldnit)){
                                                                  //welt=new _welt();
                                                                  sdworld=new _speicherbardynamisch<_welt >(&datei,sdow,ow->welt);
                                                                  ow->welt->laden(worldnit->objekt(),sdworld);
                                                                  if(worldnit->objekt()->anfang(kit))do{
                                                                   if(kit->typ()=="_material"){
                                                                    mat=ow->welt;
                                                                    mat->laden(kit,new _speicherbardynamisch<_material<_tg> >(&datei,sdworld,ow->welt));
                                                                   };
                                                                  }while(worldnit->objekt()->naechstes(kit));
                                                                  meshnodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+meshtype,meshnodes);
                                                                  if(meshnodes.anfang(meshnit))do{
                                                                   if(meshnit->objekt()->bereitsgeladen()==false){
                                                                    netz=new _netz();
                                                                    netz->einhaengen(welt);
                                                                    ladennetz<_welt>(&datei,ow,sdworld,meshnit->objekt(),netz,"_corundwelt::_welt::_netz");
                                                                   };
                                                                  }while(meshnodes.naechstes(meshnit));

                                                                  /*texturenodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+texturetype,texturenodes);
                                                                  if(texturenodes.anfang(texturenit))do{
                                                                   textur=new _textur<_tb>(welt);
                                                                   sdtexture=new _speicherbardynamisch<_textur<_tb> >(&datei,sdworld,textur);
                                                                   textur->laden(texturenit->objekt(),sdtexture);
                                                                   
                                                                   _listebasis<_bild<_tb> > bilder;
                                                                   _bild<_tb>*mit;
                                                                   _bild<_tb>*mitn;
                                                                   unsigned int i;
                                                                   maptganodes.aushaengen();
                                                                   texturenit->objekt()->holenuebertyp(worldtype+"::"+texturetype+"::"+maptgatype,maptganodes);
                                                                   if(maptganodes.anfang(maptganit))do{
                                                                    maptga=new _bild<_tb>(1,1);
                                                                    sdmap=new _speicherbardynamisch<_bild<_tb> >(&datei,sdtexture,maptga);
                                                                    maptga->laden(maptganit->objekt(),sdmap);
                                                                    maptga->tiefereskalieren(1);
                                                                    maptga->datentausch(0,2);
                                                                    maptga->einhaengen(&bilder);
                                                                   }while(maptganodes.naechstes(maptganit));
                                                                   if(bilder.anfang(mit)){
                                                                    if(mit!=0) for(i=0;i<textur->pc[0];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegenbitmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                    if(mit!=0) for(i=0;i<textur->pc[1];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegenlightmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                    if(mit!=0) for(i=0;i<textur->pc[2];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegenshadowmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                    if(mit!=0) for(i=0;i<textur->pc[3];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegenbumpmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                    if(mit!=0) for(i=0;i<textur->pc[4];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegentransmissionmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                    if(mit!=0) for(i=0;i<textur->pc[5];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegenspecularmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                    if(mit!=0) for(i=0;i<textur->pc[6];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegendetailmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                    if(mit!=0) for(i=0;i<textur->pc[7];i++){
                                                                     if(mit) mitn=mit->naechstes();
                                                                     if(mit) textur->einfuegenmaskmap(mit);
                                                                     if(mitn==mit) mit=0; else mit=mitn;
                                                                    };
                                                                   };
                                                                   bilder.loeschen();
                                                                  }while(texturenodes.naechstes(texturenit));
                                                                  */
                                                                  lightnodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+lighttype,lightnodes);
                                                                  if(lightnodes.anfang(lightnit))do{
                                                                   hvo3.setzen(1,0,0);
                                                                   light=new _licht<_tg,_to>(welt,nullvector,hvo3,10);
                                                                   sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdworld,light);
                                                                   light->laden(lightnit->objekt(),sdlight);
                                                                  }while(lightnodes.naechstes(lightnit));
                                                                  
                                                                  
                                                                  gravitationnodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+gravitationtype,gravitationnodes);
                                                                  if(gravitationnodes.anfang(gravitationnit))do{
                                                                   gravitation=new _gravitation<_tg>(welt,nullvector,10);
                                                                   sdgravitation=new _speicherbardynamisch<_gravitation<_tg> >(&datei,sdworld,gravitation);
                                                                   gravitation->laden(gravitationnit->objekt(),sdgravitation);
                                                                   if(gravitationnit->objekt()->anfang(kit)){
                                                                    if(kit->typ()=="_feld"){
                                                                     _feld<_tg>*feldt=gravitation;
                                                                     feldt->laden(kit,new _speicherbardynamisch<_feld<_tg> >(&datei,sdgravitation,feldt));
                                                                    };
                                                                   };
                                                                  }while(gravitationnodes.naechstes(gravitationnit));
                                                                  
                                                                  efeldnodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+efeldtype,efeldnodes);
                                                                  if(efeldnodes.anfang(efeldnit))do{
                                                                   efeld=new _feldelektrostatisch<_tg>(welt,nullvector,nullvector);
                                                                   sdefeld=new _speicherbardynamisch<_feldelektrostatisch<_tg> >(&datei,sdworld,efeld);
                                                                   efeld->laden(efeldnit->objekt(),sdefeld);
                                                                   if(efeldnit->objekt()->anfang(kit)){
                                                                    if(kit->typ()=="_feld"){
                                                                     _feld<_tg>*feldt=efeld;
                                                                     feldt->laden(kit,new _speicherbardynamisch<_feld<_tg> >(&datei,sdefeld,feldt));
                                                                    };
                                                                   };
                                                                  }while(efeldnodes.naechstes(efeldnit));
                                                                  
                                                                  bfeldnodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+bfeldtype,bfeldnodes);
                                                                  if(bfeldnodes.anfang(bfeldnit))do{
                                                                   bfeld=new _feldmagnetostatisch<_tg>(welt,nullvector,nullvector);
                                                                   sdbfeld=new _speicherbardynamisch<_feldmagnetostatisch<_tg> >(&datei,sdworld,bfeld);
                                                                   bfeld->laden(bfeldnit->objekt(),sdbfeld);
                                                                   if(bfeldnit->objekt()->anfang(kit)){
                                                                    if(kit->typ()=="_feld"){
                                                                     _feld<_tg>*feldt=bfeld;
                                                                     feldt->laden(kit,new _speicherbardynamisch<_feld<_tg> >(&datei,sdbfeld,feldt));
                                                                    };
                                                                   };
                                                                  }while(bfeldnodes.naechstes(bfeldnit));
                                                                  
                                                                  partikelquellespritenodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+partikelquellespritetype,partikelquellespritenodes);
                                                                  if(partikelquellespritenodes.anfang(partikelquellespritenit))do{
                                                                   partikelquellesprite=new _partikelquellesprite(welt,welt,welt,ow->pzeit,nullvector,nullvector,10,0);
                                                                   sdpartikelquellesprite=new _speicherbardynamisch<_partikelquellesprite >(&datei,sdworld,partikelquellesprite);
                                                                   partikelquellesprite->laden(partikelquellespritenit->objekt(),sdpartikelquellesprite);
                                                                   if(partikelquellespritenit->objekt()->anfang(kit))do{
                                                                    if(kit->typ()=="_partikelquelle"){
                                                                     _partikelquelle*pq=partikelquellesprite;
                                                                     pq->laden(kit,new _speicherbardynamisch<_partikelquelle>(&datei,sdpartikelquellesprite,pq));
                                                                    };
                                                                   }while(partikelquellespritenit->objekt()->naechstes(kit));
                                                                   
                                                                   
                                                                  }while(partikelquellespritenodes.naechstes(partikelquellespritenit));
                                                                  
                                                                  cameranodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+cameratype,cameranodes);
                                                                  if(cameranodes.anfang(cameranit))do{
                                                                   camera=new _kamera<_tg>(welt);
                                                                   sdcamera=new _speicherbardynamisch<_kamera<_tg> >(&datei,sdworld,camera);
                                                                   camera->laden(cameranit->objekt(),sdcamera);
                                                                  }while(cameranodes.naechstes(cameranit));
                                                                  
                                                                  zonenodes.aushaengen();
                                                                  worldnit->objekt()->holenuebertyp(worldtype+"::"+zonetype,zonenodes);
                                                                  if(zonenodes.anfang(zonenit))do{
                                                                   zone=new _partition::_zone(welt);
                                                                   sdzone=new _speicherbardynamisch<_partition::_zone >(&datei,sdworld,zone);
                                                                   zone->laden(zonenit->objekt(),sdzone);
                                                                   
                                                                   sectornodes.aushaengen();
                                                                   zonenit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype,sectornodes);
                                                                   if(sectornodes.anfang(sectornit))do{
                                                                    sektor=new _partition::_sektor(zone);
                                                                    sdsector=new _speicherbardynamisch<_partition::_sektor >(&datei,sdzone,sektor);
                                                                    sektor->laden(sectornit->objekt(),sdsector);
                                                                    
                                                                    lightnodes.aushaengen();
                                                                    sectornit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+lighttype,lightnodes);
                                                                    if(lightnodes.anfang(lightnit))do{
                                                                     hvo3.setzen(1,0,0);
                                                                     light=new _licht<_tg,_to>(sektor,nullvector,hvo3,10);
                                                                     sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdsector,light);
                                                                     light->laden(lightnit->objekt(),sdlight);
                                                                    }while(lightnodes.naechstes(lightnit));
                                                                    
                                                                    clightnodes.aushaengen();
                                                                    sectornit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+clighttype,clightnodes);
                                                                    if(clightnodes.anfang(clightnit))do{
                                                                     hvo3.setzen(1,0,0);
                                                                     clight=new _corundlicht(ow,sektor,nullvector,hvo3,10);
                                                                     clightnit->objekt()->holennamenqualifikation(clight->dateiqualifikation);
                                                                     sdclight=new _speicherbardynamisch<_corundlicht>(&datei,sdsector,clight);
                                                                     clight->laden(clightnit->objekt(),sdclight);
                                                                     clightnit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+clighttype+"::"+lighttype,lightnodes);
                                                                     if(lightnodes.anfang(lightnit)){
                                                                      hvo3.setzen(1,0,0);
                                                                      light=clight;
                                                                      sdlight=new _speicherbardynamisch<_licht<_tg,_to> >(&datei,sdclight,light);
                                                                      light->laden(lightnit->objekt(),sdlight);
                                                                     };
                                                                    }while(clightnodes.naechstes(clightnit));
                                                                    
                                                                    
                                                                    ppolygonnodes.aushaengen();
                                                                    sectornit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+ppolygontype,ppolygonnodes);
                                                                    if(ppolygonnodes.anfang(ppolygonnit))do{
                                                                     ppolygon=new _partition::_polygon((::_polygon*)0);
                                                                     ppolygon->einfuegeninsektor(sektor);
                                                                     sdppolygon=new _speicherbardynamisch<_partition::_polygon >(&datei,sdsector,ppolygon);
                                                                     ppolygon->laden(ppolygonnit->objekt(),sdppolygon);
                                                                     
                                                                     pvertexnodes.aushaengen();
                                                                     ppolygonnit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+sectortype+"::"+ppolygontype+"::"+pvertextype,pvertexnodes);
                                                                     if(pvertexnodes.anfang(pvertexnit))do{
                                                                      pvertex=new _partition::_vertex(ppolygon,nullvector);
                                                                      sdpvertex=new _speicherbardynamisch<_partition::_vertex >(&datei,sdppolygon,pvertex);
                                                                      pvertex->laden(pvertexnit->objekt(),sdpvertex);
                                                                     }while(pvertexnodes.naechstes(pvertexnit));
                                                                    }while(ppolygonnodes.naechstes(ppolygonnit));
                                                                   }while(sectornodes.naechstes(sectornit));
                                                                  
                                                                   planenodes.aushaengen();
                                                                   zonenit->objekt()->holenuebertyp(worldtype+"::"+zonetype+"::"+planetype,planenodes);
                                                                   if(planenodes.anfang(planenit))do{
                                                                    ebene=new _partition::_ebene(zone);
                                                                    sdplane=new _speicherbardynamisch<_partition::_ebene >(&datei,sdzone,ebene);
                                                                    ebene->laden(planenit->objekt(),sdplane);
                                                                   }while(planenodes.naechstes(planenit));
 
                                                                  }while(zonenodes.naechstes(zonenit));
                                                                  //lw->einhaengen(welt);
                                                                 };//weltnodes
                                                                };//ownodes
                                                                //-------------- assoziation
                                                                //t1=tt.system();
                                                                hf->statusbar->text(2,L"Szene wird geladen : Datenstruktur wird reassoziiert... ");
                                                                L->schreiben("Dateiobjektsturktur wird assoziiert.");
                                                                datei.assoziieren();
                                                                //t2=tt.system();
                                                                //-------------- statistik
                                                                //L->schreiben("------------------------- Laden einer Szene ------------------");
                                                                //L->schreiben("Zeitdauer des Ladens      [ms] : ",(int)(t1-t0));
                                                                //L->schreiben("Zeitdauer der Assoziation [ms] : ",(int)(t2-t1));
                                                                hf->statusbar->text(2,L"Szene wird geladen : Datenstruktur wird aktualisiert... ");
                                                                //-------------- aktualisieren -----------------------------------------------------------
                                                              //  ow->speichername=fn;
                                                                if(ow->welt){

                                                                 if(ow->welt->anfang(netz))do{
                                                                  netz->aktualisieren();
                                                                  _polygon*pit;
                                                                  if(netz->anfang(pit))do{
                                                                   if(pit->verwendentextur()) if(pit->textur()==0) {
                                                                    if((pit->texturstring()=="ni")||(pit->texturstring()=="null")){
                                                                    }else{
                                                                     pit->textur(ow->textur.textur(pit->texturstring()));
                                                                    };
                                                                   };
                                                                  }while(netz->naechstes(pit));
                                                                 }while(ow->welt->naechstes(netz));
                                                                 
                                                                 
                                                             
                                                                 
                                                                 
                                                                 if(ow->kamera==0){
                                                                  ow->kamera=new _corundkamera(ow);
                                                                  ow->kamera->kam->yaw(90);
                                                                 };
                                                                 
                                                                 
                                                                 _partikelquelle*pqit;
                                                                 _partikelquellesprite*pqits;
                                                                 ow->loeschenpartikelsysteme();
                                                                 if(ow->welt->anfang(pqit))do{
                                                                  pqits=dynamic_cast<_partikelquellesprite*>(pqit);
                                                                  if(pqits){
                                                                   // laden der textur zeiger
                                                                   // laden der internen partikelquellemnzeiger
                                                                   if(pqits->name()=="psstaubwolke") {ow->psstaubwolke=pqits;L->schreiben("bbbbbbbbbbbbbbbb");};
                                                                   if(pqits->name()=="psstrahl") ow->psstrahl=pqits;
                                                                   if(pqits->name()=="psrot") ow->psrot=pqits;
                                                                   if(pqits->name()=="pseinschlag") ow->pseinschlag=pqits;
                                                                   if(pqits->name()=="pskugeltot") ow->pskugeltot=pqits;
                                                                   if(pqits->name()=="psfrage") ow->psfrage=pqits;
                                                                   
                                                                   _listenknoten<_zeichenkette<char> >*tit;
                                                                   if(pqits->texturstrings()->anfang(tit))do{
                                                                    pqits->einfuegentextur(ow->textur.textur(*tit->objekt()));
                                                                   }while(pqits->texturstrings()->naechstes(tit));
                                                                  };
                                                                 }while(ow->welt->naechstes(pqit));


                                                                 _corundstein*csit;
                                                                 if(ow->anfang(csit))do{
                                                                  csit->nachbereitenkonstruktion();
                                                                 }while(ow->naechstes(csit));
                                                                 _corundobjekt*coit;
                                                                 if(ow->anfang(coit))do{
                                                                  coit->nachbereitenkonstruktion();
                                                                 }while(ow->naechstes(coit));    
                                                                 _corundstein*cbit;
                                                                 if(ow->anfang(cbit))do{
                                                                  cbit->nachbereitenkonstruktion();
                                                                 }while(ow->naechstes(cbit));


                                                                /* if(lwit->objekt()->anfang(zone))do{
                                                                  if(zone->anfang(sektor))do{ 
                                                                   sektor->aktualisieren();
                                                                  }while(zone->naechstes(sektor));
                                                                 }while(lwit->objekt()->naechstes(zone));*/
                                                                };
                                                                L->schreiben("corundwelt laden beenden.");
                                                                
                                                                
 

																/* _polygon*pit;
																 _netz*nit;
																 iterierenliste(ow->welt,nit,iterierenliste(nit,pit,pit->speicherkonversion()));
                                                               */

};
