Name         : BahnGigantTool, BahnGigantVisualizer
Author       : simugamer
Version      : 0.2
Copyright    : GNU 3 Public Licence

Beschreibung BahnGigantTool:
Erzeugt eine BMP-Datei der Gr��e 1024x1024 aus einem Memory-Dump von Bahngigant.
In der BMP sind die Grundz�ge der Karte erkennbar. Zus�tlich wird eine csv-Datei
erzeugt, die man sich z.B. in Excel anzeigen lassen kann.

Verwendung BahnGigantTool:
1.	Gew�nschte Karte in Bahngigant laden.
2.	Mit UsaMimi Hurricane den Speicherbereich 00C07554 bis 00D07553
	aus Bahngigant heraus in eine Datei dumpen
2.a		Select Process: ATrain9.exe w�hlen
2.b		Start Address: 00C07554, End Address:00D07553, Selection Size: 00100000
2.c		OK klicken
2.d		Edit(E) -> Define Selection & Generate Checksum(S)...
2.e		File(F) -> Save Selected Range as File(D)
3.	BahnGigantTool starten.
4.	Gedumpte Datei ausw�hlen.
5.	Die bmp und csv Dateien werden im gleichen Ordner wie die Eingabedatei
	gespeichert. Der Dateiname wird durch anh�ngen von .bmp und .csv gebildet.
Alternativ kann das Programm auch von der Konsole aus gestartet werden.
Der erste Parameter nach dem Programmnamen ist dabei die Eingabe-Datei.


Beschreibung BahnGigantVisualizer:
Nimmt ein Memory-Dump der Texturinformationen und ein 1024x1024 Bitmap.
An Stellen, an denen das Bitmap schwarz ist, werden die Daten in dem Dump
so ver�ndert, dass beim zur�ckladen an dieser Stelle in Bahngigant die Textur
dunkel wird. Zum r�ckg�ngigmachen eine BMP Datei laden, die kein schwarz enth�lt.

1.	Gew�nschte Karte in Bahngigant laden.
2.	Mit UsaMimi Hurricane den Speicherbereich der Texturinformation finden.
	dieses Feld ist 0x400000 gro�. eine Zelle ist 4 Byte gro� und hat die Form
	0xFF...... oder 0xC8...... . Man kann testen, ob man den richtigen Bereich
	gefunden hat, wenn man das erste FF in 00 �ndert. Ganz oben links auf der Karte
	in Bahngigant m�sste jetzt die Textur dunkel geworden sein.
	Leider ist dieses Feld bei jedem Start von Bahngigant an einer anderen Stelle im
	Speicher und es scheint auch eine Kopie zu geben.
	Diesen Bereich mit Edit(E) -> Define Selection & Generate Checksum(S)... markieren
	und in einer Datei Speichern(File(F) -> Save Selected Range as File(D)).
3.	BahnGigantVisualizer starten
3.a		Erste Datei: Bitmap-Datei
3.b		Gedumpte Texturinformation (4Mb gro�)
4.	File(F) -> Load File to Selected Range(U) in UsaMimi ausw�hlen und die
	gerade erzeugte Datei mit der Endung .out ausw�hlen.


Zum Selbst-Kompilieren wird CIMG.h ben�tigt, was es auf
http://cimg.sourceforge.net zum Download gibt.

Die Verwendung des BahnGigantTools erfolgt auf eigene Gefahr!

Weitere Informationen auf http://www.bahngigant.de/forum/index.php?a=vtopic&t=282
