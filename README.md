# Matkac_Hulajnoga_Elektryczna
Projekt Technika Mikroprocesorowa

,,Matkac-Hulajnoga Elektryczna”

Grupa Elektroniki Morskiej sem.5

Rok akademicki 2022/2023

Skład zespołu;

1.Magdalena Borowiec
2.Mateusz Aniołkowski 
3.Oskar Wawrzyniak    
4.Grzegorz Grzenkowicz  
5.Dennis Ahmed         
6.Kacper Wróblewski    
7.Dawid Sanecki 


Założenia projektowe;

•	Trzy tryby pracy

-	Zwykły

-	Z ograniczeniem mocy

-	Z ograniczeniem prędkości

•	Oświetlenie drogowe

•	Prędkościomierz (opcjonalnie)

•	Płynna regulacja prędkości

•	System monitorowania i zabezpieczenia baterii

•	Amperometryka silnika

•	Kontrola temperatury na poszczególnych podzespołach (opcjonalnie)


<a href="https://miro.com/app/board/uXjVPJqmcqU=/">Miro projektu</a>

Zestawienie materiałowe:


      Poziom 0 (produkt gotowy)        Poziom 1 (części podstawowe/komponenty)      Poziom 2 (części dodatkowe/podzespoły)          
               Hulajnoga(1szt.)	                              Koło (2szt.)	               Wyświetlacz OLED(1szt.)
	                                                         Kierownica(1szt.)	          Przetwornica napięcia(1szt.)
	                                                              Rama (1szt.)	                      Lampa LED(1szt.)
	                                                             Silnik(1szt.)	                      Hallotron(1szt.)
	                                                  Sterownik silnika(1szt.)	                        Arduino(1szt.)
	                                                            Bateria(1szt.)	                     Płytka PCB(1szt.)
	                                                       Manetka gazu(1szt.)	                     Kontaktron(1szt.)
		                                                                                            Złącza ARK(20szt.)



Opis projektu:

Przetwornica napięciowa step down  reguluje napięcie dostarczane na Arduino.  Na  kierownicy umieszczano manetkę gazu, do  której dołączamy wyświetlacz OLED sterowany za pomocą Arduino  , podłączenie za pomocą złączy ARK. Przełączanie manetki gazu, jak również hamulca i hallotronu(umieszczonego w przednim kole hulajnogi) jest realizowane za pomocą przycisków. Aby zapobiec  drganiom styków podczas przełączania zastosowano debouncing, realizowany przez dodatkowy rezystor oraz komendę PULLUP w komunikacji z arduino. Na kierownicy umieszczono również lampę LED, sterowaną Arduino , napięcie dostarczane do lamp jest regulowane przez dwa tranzystory Mosfet. Na wyjściu z baterii umieszczono dzielnik napięcia w celu zredukowania napięcia  z 42V do 5V. Czujnik prędkości zrealizowano za pomocą kontaktronu umieszczono w tylnim kole hulajnogi, który umożliwia zliczanie obrotów koła, informacje dostarczone do Arduino przeliczamy i wyświetlamy na wyświetlaczu OLED jako informacja o prędkości  jazdy.

Testy przeprowadzone przez Mateusza Aniołkowskiego wykazały skuteczność zastosowanych rozwiązań.

W projekcie zrealizowano:

•	oświetlenie drogowe

•	prędkościomierz

•	płynna regulacja prędkości

Z początkowych założeń nie udało  się zrealizować :

•	Trzy tryby pracy

-	Zwykły

-	Z ograniczeniem mocy

-	Z ograniczeniem prędkości

•	System monitorowania i zabezpieczenia baterii

•	Amperometryka silnika

•	Kontrola temperatury na poszczególnych podzespołach 

