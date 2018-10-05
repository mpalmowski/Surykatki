Mateusz Palmowski 277017

AAL-8 -LS Surykatki
Surykatki z Afryki przeprawiaj� si� przez rzek� skacz�c po grzbietach p�ywaj�cych po niej krokodyli.
Poniewa� jest to ryzykowna czynno��, surykatki zawsze wybieraj� tras� wymagaj�c� najmniejszej liczby skok�w.
Stado surykatek stoi w szeregu wzd�u� linii brzegowej rzeki.
Dla ka�dej surykatki wyznacz optymaln� tras� przeprawy przez rzek�.
Surykatki mog� przemieszcza� si� wzd�u� brzegu skokami, kt�re licz� si� do d�ugo�ci trasy.
Znane s�: szeroko�� rzeki, zasi�g skoku surykatki, liczba i po�o�enie krokodyli (nale�y je traktowa� jak odcinki o znanych ko�cach), liczba i po�o�enie surykatek.

Tryby wywo�ania:
	-m1: Pobierz dane ze standardowego wej�cia i wypisz wynik na standardowe wyj�cie. np. Surykatki -m1 <<in.txt

	-m2: Wygeneruj instancj� problemu i rozwi��. Wypisz wynik na standardowe wyj�cie. np. Surykatki -m2 -n100

	-m3: Przeprowad� ca�y proces testowania z pomiarem czasu dla rosn�cego n i por�wnaniem ze z�ozono�ci� teoretyczn�. np. Surykatki -m3 -n100 -k10 -step200 -r10

	-gen:	Wygeneruj instancj� problemu i wypisz wynik na standardowe wyj�cie. np. Surykatki -gen -n100 >>out.txt

Parametry:
	-n: Ilo�� krokodyli.
	
	-k: Ilo�� krok�w.

	-step: Warto��, o jak� inkrementowana jest liczba krokodyli z ka�dym krokiem.

	-r: Ilo�� powt�rze� w ka�dym kroku.

Dzia�anie:
	Program tworzy graf na podstawie mo�liwych skok�w mi�dzy krokodylami.
	Wykorzystuje w tym celu metod� Brute Force (O(n^2)) lub metod� Rastrow� (O(n)).
	Nast�pnie znajduje �cie�ki w grafie, u�ywaj�c algorytmu Breadth First Search (O(E + V)).

Struktury danych:
	Graf - dwu-wymiarowa tablica liczb ca�kowitych

	Pixel Map - dwu-wymiarowa tablica wska�nik�w na obiekty typu Pixel.

	Pixel - struktura posiadaj�ca tablic� liczb ca�kowitych oraz informacj� o liczbie element�w.
	Pocz�tkowo rozmiar tablicy wynosi 0.
	Dodaj�c nowy element, tworzona jest nowa tablica o rozmiarze wiekszym o 1 i usuwana jest stara tablica.
	Struktura ta ma za zadanie maksymalizacj� oszcz�dno�ci miejsca w pami�ci.

Pliki �r�d�owe:
	BruteForce.hpp - Klasa i metody s�u��ce do tworzenia grafu metod� Brute Force.

	Controller.hpp - Analiza argument�w wej�ciowych programu, tryby uruchomienia i najwa�niejsze sta�e.

	Crocodile.hpp - Klasa reprezentuj�ca krokodyla.

	Generator.hpp - Generowanie losowej tablicy o zadanych parametrach.

	Graph.hpp - Klasa reprezentuj�ca graf i posiadaj�ca najwazniejsze metody do interakcji z nim (w tym algorytm BFS).

	main.cpp - Start programu, wywo�anie Controller'a.

	PixelMap.hpp - Klasa reprezentuj�ca map� pikseli i posiadaj�ca metody tworzenia jej oraz wizualizacji.

	Point.hpp - Prosta struktura, reprezentuj�ca punkt w dwu-wymiarowej przestrzeni.

	Raster.hpp - Klasa i metody s�u��ce do tworzenia grafu metod� Rastrow�.

	Solver.h / Solver.cpp - Klasa s�u��ca do rozwi�zania problemu surykatek.
	Posiada metody do inicjalizacji grafu, sortowania krokodyli, znajdowania drogi pomi�dzy surykatk�,
	a krokodylem, oraz generowania danych wyj�ciowych. Dziedzicz� po niej BruteForce oraz Raster.

	Statistics.hpp - Klasa mierz�ca czas dzia�ania programu oraz generuj�ca statystyk� z�ozono�ci obliczeniowej.

	Pixel.hpp - Klasa reprezentuj�ca pojedynczy piksel w mapie pikseli.
	Od tradycyjnego podej�cia r�ni si� tym, �e jeden piksel mo�e mie� wiele warto�ci jednocze�nie.