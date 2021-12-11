A c PROGRAM to create a virtual cpu with the simplest architecture

WHY C :
It's a very simple language that allows the writing of concise programs.
It's a low level language with some high-level features. This makes it a good choice for creating a VM.

Pour compiler taper les 3 commandes suivante
make -f Makefile
python3 python/compiler.py
./VCORE sources/code sources/regState 1 (ou 0)


Pour ce qui est du Doxyfile, il suffit de :
	doxygen Doxyfile
	puis allez dans le dossier html, puis ouvrez index.html et dans l'onglet fichiers
