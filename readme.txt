Mateusz Palmowski 277017

AAL-8 -LS Surykatki
Surykatki z Afryki przeprawiaj¹ siê przez rzekê skacz¹c po grzbietach p³ywaj¹cych po niej krokodyli.
Poniewa¿ jest to ryzykowna czynnoœæ, surykatki zawsze wybieraj¹ trasê wymagaj¹c¹ najmniejszej liczby skoków.
Stado surykatek stoi w szeregu wzd³u¿ linii brzegowej rzeki.
Dla ka¿dej surykatki wyznacz optymaln¹ trasê przeprawy przez rzekê.
Surykatki mog¹ przemieszczaæ siê wzd³u¿ brzegu skokami, które licz¹ siê do d³ugoœci trasy.
Znane s¹: szerokoœæ rzeki, zasiêg skoku surykatki, liczba i po³o¿enie krokodyli (nale¿y je traktowaæ jak odcinki o znanych koñcach), liczba i po³o¿enie surykatek.

Tryby wywo³ania:
	-m1: Pobierz dane ze standardowego wejœcia i wypisz wynik na standardowe wyjœcie. np. Surykatki -m1 <<in.txt

	-m2: Wygeneruj instancjê problemu i rozwi¹¿. Wypisz wynik na standardowe wyjœcie. np. Surykatki -m2 -n100

	-m3: PrzeprowadŸ ca³y proces testowania z pomiarem czasu dla rosn¹cego n i porównaniem ze z³ozonoœci¹ teoretyczn¹. np. Surykatki -m3 -n100 -k10 -step200 -r10

	-gen:	Wygeneruj instancjê problemu i wypisz wynik na standardowe wyjœcie. np. Surykatki -gen -n100 >>out.txt

Parametry:
	-n: Iloœæ krokodyli.
	
	-k: Iloœæ kroków.

	-step: Wartoœæ, o jak¹ inkrementowana jest liczba krokodyli z ka¿dym krokiem.

	-r: Iloœæ powtórzeñ w ka¿dym kroku.

Dzia³anie:
	Program tworzy graf na podstawie mo¿liwych skoków miêdzy krokodylami.
	Wykorzystuje w tym celu metodê Brute Force (O(n^2)) lub metodê Rastrow¹ (O(n)).
	Nastêpnie znajduje œcie¿ki w grafie, u¿ywaj¹c algorytmu Breadth First Search (O(E + V)).

Struktury danych:
	Graf - dwu-wymiarowa tablica liczb ca³kowitych

	Pixel Map - dwu-wymiarowa tablica wskaŸników na obiekty typu Pixel.

	Pixel - struktura posiadaj¹ca tablicê liczb ca³kowitych oraz informacjê o liczbie elementów.
	Pocz¹tkowo rozmiar tablicy wynosi 0.
	Dodaj¹c nowy element, tworzona jest nowa tablica o rozmiarze wiekszym o 1 i usuwana jest stara tablica.
	Struktura ta ma za zadanie maksymalizacjê oszczêdnoœci miejsca w pamiêci.

Pliki Ÿród³owe:
	BruteForce.hpp - Klasa i metody s³u¿¹ce do tworzenia grafu metod¹ Brute Force.

	Controller.hpp - Analiza argumentów wejœciowych programu, tryby uruchomienia i najwa¿niejsze sta³e.

	Crocodile.hpp - Klasa reprezentuj¹ca krokodyla.

	Generator.hpp - Generowanie losowej tablicy o zadanych parametrach.

	Graph.hpp - Klasa reprezentuj¹ca graf i posiadaj¹ca najwazniejsze metody do interakcji z nim (w tym algorytm BFS).

	main.cpp - Start programu, wywo³anie Controller'a.

	PixelMap.hpp - Klasa reprezentuj¹ca mapê pikseli i posiadaj¹ca metody tworzenia jej oraz wizualizacji.

	Point.hpp - Prosta struktura, reprezentuj¹ca punkt w dwu-wymiarowej przestrzeni.

	Raster.hpp - Klasa i metody s³u¿¹ce do tworzenia grafu metod¹ Rastrow¹.

	Solver.h / Solver.cpp - Klasa s³u¿¹ca do rozwi¹zania problemu surykatek.
	Posiada metody do inicjalizacji grafu, sortowania krokodyli, znajdowania drogi pomiêdzy surykatk¹,
	a krokodylem, oraz generowania danych wyjœciowych. Dziedzicz¹ po niej BruteForce oraz Raster.

	Statistics.hpp - Klasa mierz¹ca czas dzia³ania programu oraz generuj¹ca statystykê z³ozonoœci obliczeniowej.

	Pixel.hpp - Klasa reprezentuj¹ca pojedynczy piksel w mapie pikseli.
	Od tradycyjnego podejœcia ró¿ni siê tym, ¿e jeden piksel mo¿e mieæ wiele wartoœci jednoczeœnie.