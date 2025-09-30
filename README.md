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
|1|0 (5)|output2.txt x2, output3.txt x2, output4.txt x1| <img width="130" height="54" alt="Screenshot 2025-09-27 172428" src="https://github.com/user-attachments/assets/80184e01-7dd4-4f2c-8f32-9aeb0cd21def" /> | visos kolizijos turi tuos pačius slaptažodžius, tad jų negalime skaičiuoti kaip kolizijų. Po testo pakeičiau kodą, kad tokių neskaičiuotų |
|2|0||<img width="102" height="76" alt="image" src="https://github.com/user-attachments/assets/146d9601-4db5-40d3-8f59-2626da8a95f3" />|pakeitus kodą nebeliko kolizijų|
|3|0||<img width="102" height="76" alt="image" src="https://github.com/user-attachments/assets/f7487588-733b-476f-bd2a-1652f67230be" />||
|4|0||<img width="102" height="76" alt="image" src="https://github.com/user-attachments/assets/f2e9413f-5982-43ae-8877-d699c802a8eb" />||
|5|0||<img width="101" height="75" alt="image" src="https://github.com/user-attachments/assets/17ead738-34df-4926-9c28-83f8d196eba5" />||
|vidurkis|0|||tikrųjų kolizijų per visus 5 bandymus nebuvo|

## 2 testas ##
Testo tikslas - lavinos efekto analizė.  
Atlikus testą, rezultatai parodė, kad trumpesni slaptažodžiai turėjo didžiausią pasikartojimų dažnį.  
Šiame teste buvo generuojami tie patys failai su 10, 100, 500 ir 1000 simbolių ilgio slaptažodžiais. Visi po 100,000 eilučių.  
Tačiau šįkart slaptažodžiai keitėsi tarpusavyje tik po vieną simbolį.  
Kolizijų failuose aptikta nebuvo.  

REZULTATAI:  

5 testų vidurkis:
| Slaptažodžio simbolių kiekis (failas) | Vidutiniškai panaudotų unikalių simbolių pozicijoje (16 max, geriausias rezultatas) | Daugiausiai pasikartojusių simbolių dažnio vidurkis | Mažiausiai pasikartojančių simbolių dažnio vidurkis | Vidutinis pasikartojimo dažnis | daugiausiai pasikartojusio simbolio dažnis vienoje pozicijoje (pozicija) | Bitų lygmens pasikartojimo dažnio vidurkis |
| ------------- | ------------ | ----------------------------------- | --------- | ---------- | ---------- | ---------- |
|10 (output1.txt)|15.636|28.886%|2.202%|6.478%|80.578% (3 iš 5 - 23 pozicijoje)|46.886%|
|100 (output2.txt)|15.98|6.738%|3.086%|6.26%|7.37% (visada 3 pozicijoje)|51.892%|
|500 (output3.txt)|15.98|6.738%|3.092%|6.26%|7.142% (4 iš 5 - 3 pozicijoje)|51.924%|
|1000 (output4.txt)|15.98|6.752%|3.098%|6.26%|7.118% (2 iš 5 - 7 pozicijoje, 1 - 3 poz.)|51.906%|
|vidurkis (visi failai)|15.894|12.279%|2.870%|6,315%|25.552%|50.652%|


1 testavimas:
| Slaptažodžio simbolių kiekis (failas) | Vidutiniškai panaudotų unikalių simbolių pozicijoje (16 max, geriausias rezultatas) | Daugiausiai pasikartojusių simbolių dažnio vidurkis | Mažiausiai pasikartojančių simbolių dažnio vidurkis | Vidutinis pasikartojimo dažnis | daugiausiai pasikartojusio simbolio dažnis vienoje pozicijoje (pozicija) | Bitų lygmens pasikartojimo dažnio vidurkis | nuotrauka | komentaras |
| ------------- | ------------ | ----------------------------------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
|10 (output1.txt)|15.59|28.04%|2.20%|6.56%|83.55% (26)|47.94%|<img width="85" height="14" alt="image" src="https://github.com/user-attachments/assets/479cc2b5-c4bc-4d09-93eb-f63ded33d354" />|Mažesniame faile pasikartojimų vidurkiai prastesni|
|100 (output2.txt)|15.98|6.75%|3.09%|6.26%|7.44% (3)|51,89%|<img width="85" height="14" alt="image" src="https://github.com/user-attachments/assets/ad8e5a33-54bc-4efe-a21a-852987872d39" />|Paprastas vidurkis daug mažesnis, bet bitų lygmenyje pakilo|
|500 (output3.txt)|15.98|6.74%|3.09%|6.26%|7.05% (3)|51.93%|<img width="85" height="14" alt="image" src="https://github.com/user-attachments/assets/b5cc075a-acef-4ea9-9926-d770a63288cb" />||
|1000 (output4.txt)|15.98|6.76%|3.10%|6.26%|7.21% (11)|51,93%|<img width="85" height="14" alt="image" src="https://github.com/user-attachments/assets/a62e16fa-652b-4541-99d8-1f050ff3e690" />||


2 testavimas:
| Slaptažodžio simbolių kiekis (failas) | Vidutiniškai panaudotų unikalių simbolių pozicijoje (16 max, geriausias rezultatas) | Daugiausiai pasikartojusių simbolių dažnio vidurkis | Mažiausiai pasikartojančių simbolių dažnio vidurkis | Vidutinis pasikartojimo dažnis | daugiausiai pasikartojusio simbolio dažnis vienoje pozicijoje (pozicija) | Bitų lygmens pasikartojimo dažnio vidurkis | nuotrauka | komentaras |
| ------------- | ------------ | ----------------------------------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
|10 (output1.txt)|15.64|30.31%|2.18%|6.46%|95.74% (47)|46,28%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/7cb5e481-f389-4243-ba98-4f63d8263ef0" />|Bitų pasiskirstymo vidurkis geresnis nei hex|
|100 (output2.txt)|15.98|6.73%|3.08%|6.26%|7.27% (3)|51,89%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/03090f82-10b2-4fa5-9f28-7a928701b38a" />|Bitų vidurkis prastesnis nei trumpo slaptažodžio faile, bet hex'ų vidurkis daug geresnis|
|500 (output3.txt)|15.98|6.74%|3.09%|6.26%|7.15% (3)|51,91%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/24c8a4c8-d249-4b86-950e-ddad220fbc57" />|pastebime, kad trečioje pozicijoje dažnai kartojasi didžiausias pasikartojimo rodiklis|
|1000 (output4.txt)|15.98|6.74%|3.10%|6.26%|7.06% (7)|51,88%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/ad15d3fa-18a3-4abf-af4e-10822c60d75a" />|pastebime, kad nuo antro failo, visuose failuose unikalių simbolių vienoje pozicijoje vidurkis dažniausiai yra 15.8. Taip nutinka dėl to, kad mano kodo sugeneruotas pirmasis simbolis (pozicija) visuose 100,000 hash turi tik 15 iš 16 simbolių.|


3 testavimas:
| Slaptažodžio simbolių kiekis (failas) | Vidutiniškai panaudotų unikalių simbolių pozicijoje (16 max, geriausias rezultatas) | Daugiausiai pasikartojusių simbolių dažnio vidurkis | Mažiausiai pasikartojančių simbolių dažnio vidurkis | Vidutinis pasikartojimo dažnis | daugiausiai pasikartojusio simbolio dažnis vienoje pozicijoje (pozicija) | Bitų lygmens pasikartojimo dažnio vidurkis | nuotrauka |
| ------------- | ------------ | ----------------------------------- | --------- | ---------- | ---------- | ---------- | ---------- |
|10 (output1.txt)|15.66|27.85%|2.24%|6.45%|63.70% (23)|46,34%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/2cdd2073-7998-4298-bf6f-b69e7bb850e9" />|
|100 (output2.txt)|15.98|6.74%|3.09%|6.26%|7.34% (3)|51,90%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/958ea0e3-1adb-4444-9aaf-c6150ea1914d" />|
|500 (output3.txt)|15.98|6.74%|3.09%|6.26%|7.08% (13)|51,93%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/a0fed995-83db-463a-99fd-45b64380326b" />|
|1000 (output4.txt)|15.98|6.76%|3.09%|6.26%|7.05% (21)|51,91%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/5df68aea-78f4-428e-80b4-4ed7a990a930" />|


4 testavimas:
| Slaptažodžio simbolių kiekis (failas) | Vidutiniškai panaudotų unikalių simbolių pozicijoje (16 max, geriausias rezultatas) | Daugiausiai pasikartojusių simbolių dažnio vidurkis | Mažiausiai pasikartojančių simbolių dažnio vidurkis | Vidutinis pasikartojimo dažnis | daugiausiai pasikartojusio simbolio dažnis vienoje pozicijoje (pozicija) | Bitų lygmens pasikartojimo dažnio vidurkis | nuotrauka | komentaras |
| ------------- | ------------ | ----------------------------------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
|10 (output1.txt)|15.73|28.05%|2.19%|6.39%|63.24% (23, 39, 47)|46,7%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/cb6d863e-f9c9-480d-a126-aee5b2d91035" />| didžiausias pasikartojimas įvyko 3 pozicijose |
|100 (output2.txt)|15.98|6.73%|3.09%|6.26%|7.41% (3)|51,88%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/78cad9cd-843a-4d68-94e9-2a794545422e" />||
|500 (output3.txt)|15.98|6.74%|3.09%|6.26%|7.33% (3)|51,93%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/b44844a5-eb8d-4c0f-8f49-1af87aa310dc" />||
|1000 (output4.txt)|15.98|6.75%|3.09%|6.26%|7.14% (3)|51,91%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/f2e2a552-15ec-4363-9b45-0c55953f931e" />||


5 testavimas:
| Slaptažodžio simbolių kiekis (failas) | Vidutiniškai panaudotų unikalių simbolių pozicijoje (16 max, geriausias rezultatas) | Daugiausiai pasikartojusių simbolių dažnio vidurkis | Mažiausiai pasikartojančių simbolių dažnio vidurkis | Vidutinis pasikartojimo dažnis | daugiausiai pasikartojusio simbolio dažnis vienoje pozicijoje (pozicija) | Bitų lygmens pasikartojimo dažnio vidurkis | nuotrauka | komentaras |
| ------------- | ------------ | ----------------------------------- | --------- | ---------- | ---------- | ---------- | ---------- | ---------- |
|10 (output1.txt)|15.56|30.18%|2.20%|6.53%|96.66% (23)|47,17%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/edd6ee87-cbfd-4252-8e26-76ae7d044bbc" />||
|100 (output2.txt)|15.98|6.74%|3.08%|6.26%|7.39% (3)|51,90%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/a1e40abe-7312-4bad-95ec-4bc3f59a582c" />||
|500 (output3.txt)|15.98|6.73%|3.10%|6.26%|7.10% (3)|51,92%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/72ad3a8e-e849-4c48-80b3-ffa5ec2b8e8e" />||
|1000 (output4.txt)|15.98|6.75%|3.11%|6.26%|7.13% (7)|51.90%|<img width="85" height="17" alt="image" src="https://github.com/user-attachments/assets/e9cf9cbe-9fa2-4e96-ac2b-842a47be0879" />||

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
