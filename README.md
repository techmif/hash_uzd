# hash_uzd
Blokų grandinių technologijų užduotis sukurti hash funkciją.

Darbą atlikome poroje.  
Marijus Kuprys atliko dalį be AI pagalbos (pasiskirstėme rolėmis mesdami monetą)  
Dominykas Pronskus atliko dalį su AI pagalba  

# __Užduoties atlikimo procesas__ #
## užduotis be DI pagalbos ##
1. apsirašiau idėją, sukūriau ideja.txt
2. pasidariau paprastą projekto struktūrą (atskirą branch, main.cpp ir lib.hpp failus)
3. įrašiau 2-3s audio irasas.mp3 (gali buti rodo .m4a, bet originaliai buvo mp3), kurį naudojau pagal tai, ką planavau idėjoje. Įrašas veikia, jį galima išklausyti.
4. įrašą peržiūrėjau per notepad, iš pradžių išsigandau simbolių įvairove:
   <img width="803" height="528" alt="image" src="https://github.com/user-attachments/assets/9649c1d4-aad2-492a-8338-884012710c72" />  
   Atlikau įrašo analizę. Pasinaudodamas https://www.webatic.com/encoding-explorer atradau, kad įrašo txt formatas yra unicode/utf8 formato.  
   Tuomet pabandžiau pasižiūrėti, ar veiktų konvertavimas.  
   Konvertavau tekstą (pasinaudodamas konvertavimo įrankiu per google) į binary formato tekstą. Po to konvertavau atgal į unicode ir pabandžiau paleisti failą.  
   Failas veikė, vadinasi galima rašyti funkciją, kuri nuskaitytų tekstą iš failo.  
   Jei būtų neveikęs konvertavimas, būtų tekę imtis paprastesnio sprendimo, kuris neturi utf koduotės.
5. pakeičiau projekto parametrus: padariau, kad įvestis ir išvestis veiktų su utf8 koduote (čia dar nepadariau iš tikro)
6. parašiau nuskaitymo iš mp3 funkciją (čia dar nepadariau iš tikro)
7. parašiau paskirstymo pagal vartotojo įvedimą funkciją (čia dar nepadariau iš tikro)
8. parašiau hash funkciją. Tai yra xor ir kovertavimą į x16 sistemą. (čia dar nepadariau iš tikro)
