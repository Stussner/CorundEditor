//******************************************************************************************************************************************************************************************************
//  Projekt      : corundeditor / corund
//  Bibliothek   : 
//  Modul        : _corundspeicherbar.hpp
//  Datum        : 04.04.2006
//  Beschreibung : laden und speichern der corundwelt
//******************************************************************************************************************************************************************************************************
#ifndef corundspeicherbarhpp
#define corundspeicherbarhpp

#include "../hpp/_corundeditor.hpp"

void corundweltspeichern(_hauptfenster*,_zeichenkette<char> fn,_corundwelt*ow);
void corundweltladen(_hauptfenster*,_zeichenkette<char> fn,_corundwelt*&,_grafik*,_akustik*);

#endif