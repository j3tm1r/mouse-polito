========================================================================
    LIBRERIA A COLLEGAMENTO DINAMICO: cenni preliminari sul progetto 
                                      Dll
========================================================================

La creazione guidata applicazione ha creato questa DLL 
Dll.

Questo file contiene un riepilogo del contenuto di ciascun file che
costituisce l'applicazione Dll.


Dll.vcproj
    File di progetto principale per i progetti VC++ generati tramite una 
    creazione guidata applicazione.
    Contiene informazioni sulla versione di Visual C++ che ha generato il file e
    informazioni sulle piattaforme, sulle configurazioni e sulle funzionalità 
    del progetto selezionate con creazione guidata applicazione.

Dll.cpp
    File di origine della DLL principale.

	Una volta creata, questa DLL non esporta alcun simbolo. Di conseguenza, 
        non produrrà un file LIB quando viene compilata. Se si desidera 
        impostare questo progetto come dipendenza di un altro progetto sarà 
        necessario aggiungere il codice per esportare alcuni simboli dalla DLL 
        in modo da produrre una libreria di esportazione oppure impostare la 
        proprietà Ignore Input Library su Yes nella pagina delle proprietà 
        Generale della cartella Linker nella finestra di dialogo Pagine delle 
        proprietà del progetto.

/////////////////////////////////////////////////////////////////////////////
Altri file standard:

StdAfx.h, StdAfx.cpp
    Tali file vengono utilizzati per compilare un file di intestazione 
    precompilato (PCH) denominato Dll.pch e un file dei tipi 
    precompilato denominato StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Altre note:

La creazione guidata applicazione utilizza i commenti "TODO:" per indicare le 
parti del codice sorgente da aggiungere o personalizzare.

/////////////////////////////////////////////////////////////////////////////
