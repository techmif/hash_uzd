# hash_uzd
Blokų grandinių technologijų užduotis sukurti hash funkciją.

Darbą atlikome poroje.  
Marijus Kuprys atliko dalį be AI pagalbos (pasiskirstėme rolėmis mesdami monetą)  
Dominykas Pronskus atliko dalį su AI pagalba  

# __Testavimo rezultatai__ #
## 1 testas ##
Testo tikslas - kolizijų atsparumo analizė.  
Šiame teste sugeneravau 4 failus po 100,000 atsitiktine tvarka sugeneruotų slaptažodžių ir kiekvienam iš jų sukūriau po hash.  
output1.txt - 100,000 atsitiktine tvarka sugeneruotų slaptažodžių, kuriuos sudaro tik 10 simbolių.  
output2.txt - toks pats kiekis, sudarytas iš 100 simbolių.  
output3.txt - toks pats kiekis, sudarytas iš 500 simbolių slaptažodžių.  
output4.txt - toks pats kiekis slaptažodžių, sudarytų iš 1000 simbolių.  

REZULTATAI:
| Testo numeris | kolizijų sk. | failai, kuriuose kolizijos aptiktos | nuotrauka | komentaras |
| ------------- | ------------ | ----------------------------------- | --------- | ---------- |
|1|5|output2.txt x2, output3.txt x2, output4.txt x1| <img width="130" height="54" alt="Screenshot 2025-09-27 172428" src="https://github.com/user-attachments/assets/80184e01-7dd4-4f2c-8f32-9aeb0cd21def" /> | visos kolizijos turi tuos pačius slaptažodžius, po testo pakeičiau kodą, kad tokių neskaičiuotų |
|2|0|||
|3||||
|4||||
|5||||
|vidurkis||||

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
5. padariau, kad nuskaitomas failas būtų iškart dekoduojamas į binariąją seką.
6. parašiau nuskaitymo iš mp3 funkciją.
7. parašiau vartotojo įvedimo funkciją, kuri prideda „mini saltingą“ (taip vadinu, nes visiems pridedamas vienodas).
8. parašiau paskirstymo pagal vartotojo įvedimą funkciją. (įvedimo dešimtainės ascii vertės susumuojamos ir xor metu kreipiasi į nuskaitytą ir paskirstytą mp3 vektorių)
9. parašiau hash funkciją. Tai yra xor ir kovertavimą į x16 sistemą.
10. padariau, kad hash visada būtų 64 simbolių ilgio. Per trumpi hash prideda tiek kiek trūkstą papildomų simbolių iš įvesties iš naujo, xorinama su kita mp3 vieta nei iš pradžių.
11. padariau collision handling (šiuo metu 123________ ir 222________ skiriasi tik pirmi 3 simboliai.).
12. pakeičiau mini saltingą į normalų salting su seed-based random generavimu.
13. sukūriau testinius failus ir testines funkcijas. Testavimo rezultatus aprašiau žemiau.
