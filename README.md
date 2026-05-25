TO MI WYPLUL GEMINI ZEBYSMY MOGŁY RAZEM MWAH MWAHHHH!!!!!!!!!!!!!!!
ale też sprawa bo ja nie robie w visual studio code, tylko visual studio community czy jak to tam, to fioloetowa ikonka jest... bo tak bylo prosciej te glupie biblioteki zainstalowac 

Krok 2: Wypchnięcie kodu (Push)
Gdy już się zalogujesz, w tym samym oknie upewnij się, że nazwa repozytorium (Local path / Repository Name) jest poprawna (np. ProjektC lub Snake-Zaliczenie).

Możesz zaznaczyć opcję Repozytorium prywatne (Private repository), jeśli nie chcesz, by cały świat widział Wasz kod przed oceną. Będziesz musiała potem dodać koleżankę do współpracowników na stronie GitHuba.

Kliknij niebieski przycisk na dole Utwórz i wypchnij (Create and Push).

Visual Studio w tle zapakuje Wasz kod i wyśle go na serwer. Na dole w pasku stanu pojawi się informacja o pomyślnym wypchnięciu do "origin/master" (lub "origin/main").

Jak koleżanka ma to teraz otworzyć?
To jest najważniejszy moment i największa zaleta tego, że wzięłyśmy drogę z Visual Studio i menedżerem paczek NuGet. Twoja koleżanka nie musi niczego instalować ani konfigurować ręcznie!

Oto co musi zrobić Twoja koleżanka (wyślij jej to):

Uruchamia u siebie Visual Studio.

Na ekranie startowym klika Sklonuj repozytorium (Clone a repository) i wkleja link do Waszego GitHuba.

Kiedy projekt się pobierze i otworzy, w Eksploratorze rozwiązań klika dwukrotnie na plik z zieloną ikonką o nazwie ProjektC.sln (to jest plik "Rozwiązania", który trzyma wszystkie ustawienia).

Magia: Kiedy koleżanka wciśnie F5, żeby uruchomić grę, Visual Studio zorientuje się, że brakuje biblioteki Allegro 5, połączy się z serwerem i automatycznie ją pobierze i zainstaluje specjalnie dla jej komputera, po czym uruchomi grę.
