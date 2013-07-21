Name         : BahnGigantTool
Author       : simugamer
Version      : 0.1
Copyright    : GNU 3 Public Licence

Beschreibung:
Erzeugt eine BMP-Datei der Größe 1024x1024 aus einem Memory-Dump von Bahngigant.
In der BMP sind die Grundzüge der Karte erkennbar. Zusätlich wird eine csv-Datei
erzeugt, die man sich z.B. in Excel anzeigen lassen kann.

Verwendung:
1.	Gewünschte Karte in Bahngigant laden.
2.	Mit UsaMimi Hurricane den Speicherbereich 00C07554 bis 00D07553
	aus Bahngigant heraus in eine Datei dumpen
2.a		Select Process: ATrain9.exe wählen
2.b		Start Address: 00C07554, End Address:00D07553, Selection Size: 00100000
2.c		OK klicken
2.d		Edit(E) -> Define Selection & Generate Checksum(S)...
2.e		File(F) -> Save Selected Range as File(D)
3.	BahnGigantTool starten.
4.	Gedumpte Datei auswählen.
5.	Die bmp und csv Dateien werden im gleichen Ordner wie die Eingabedatei
	gespeichert. Der Dateiname wird durch anhängen von .bmp und .csv gebildet.

Alternativ kann das Programm auch von der Konsole aus gestartet werden.
Der erste Parameter nach dem Programmnamen ist dabei die Eingabe-Datei.

Zum Selbst-Kompilieren wird CIMG.h benötigt, was es auf
http://cimg.sourceforge.net zum Download gibt.

Die Verwendung des BahnGigantTools erfolgt auf eigene Gefahr!

Weitere Informationen auf http://www.bahngigant.de/forum/index.php?a=vtopic&t=282
