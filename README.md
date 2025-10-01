# Pradžia
Blokų grandinių technologijų užduotis sukurti hash funkciją.

Darbą atlikome poroje.  
Marijus Kuprys atliko dalį be AI pagalbos (pasiskirstėme rolėmis mesdami monetą)  
Dominykas Pronskus atliko dalį su AI pagalba  

Ši užduoties dalis daryta pasitelkiant AI įrankiais (ChatGPT, Clyde etc.).

# Hash veikimo principas

1. Funkcija priima tekstinę įvestį (string) ir pasirenkamą druskos reikšmę.
2. Inicijuoja pradinę 64-bitų būseną (state), ją pakoreguodama druska, jei druska nenurodyta, tada naudojama 0;
3. Paruoštas nedidelis 10 pirminių skaičių masyvas.
4. Pereina per kiekvieną įvesties simbolį:
   
   4.1. Paimamas simbolio baitas;
   
   4.2. Prie jo pridedama pozicijos svoris (i << 8), kad pozicija turėtų įtaką;
   
   4.3. Padauginama iš ciklinio pirminio skaičiaus;
   
   4.4. Įmaišomi keli bitai iš druskos;
   
6. Pasibaigus ciklui papildomai įmaišomas bendras įvesties ilgis ir druska.
7. Atliekamas galutinė lavina, tam kad beveik kiekvienas įvesties pokytis keistų daugumą išėjimo bitų;
8. Grąžinamas 64-bitų sveikasis skaičius (uint64_t), kurį galima rodyti dešimtainiu arba šešioliktainiu formatu.

# Darbo eiga

1. Forkinau main repo, kad release'as nesimuštu su mano grupioko release'u
2. Visų pirmą padariau meniu, kad programą būtų lengva naudoti.
3. Paprašiu free ChatGPT hashinimo funkcijos, gavosi "Chaotic Prime Mixer Hash" funkcija, kuri matoma programoje.
4. Sukūriau funkcijas rankinio arba failo įvesties.
5. Pradėjau kurti testines funkcijas eksperimentams 🔬.
6. Testinės funkcijos sukurtos.
7. Palyginau savo hash'a su SHA-256.
8. Nelyginau savo hash'o su kursiokų hash'ais, nes užduotis reikalauja ne AI padarytos funkcijos.

# Eksperimentai

1. Failai sukurti, hash'as veikia su visais.
2. Pasinaudojant pirma testine funkcija, įvedus bet kokį .txt failą, visada gaunasi tokio pat ilgio hex skaičius.
3. Pasinaudojant antra testine funkcija, yra premade funkcijos kurios pasikartoja viena pio kitos ir gaunasi ta pats decimal bei hex skaičius.
4. Pasinaudojant trečia funkcija gauname vidutinį laiko rezultatą iš konstitucija.txt failo hashuojant eksponentiškai didėjantį linijų kiekį po 20 kartų. Rezultatai:

<img width="396" height="197" alt="image" src="https://github.com/user-attachments/assets/aa32be99-9195-4473-b1be-67bf0ddaba09" />

<img width="786" height="481" alt="image" src="https://github.com/user-attachments/assets/5c88795f-759a-4a32-b69d-2bca38f48619" />

5. Kolizijų paieška. Panaudojant ketvirtą testinę funkciją, gauname failo pasirinkimą kurio elementus hash'uoja ir playgina. Rezultatai pateikiami procentais:

10 ilgio simbolių poros

<img width="349" height="109" alt="image" src="https://github.com/user-attachments/assets/62f2bd1f-b079-4698-9b79-b376ae0ecdf1" />

100 ilgio simbolių poros

<img width="354" height="111" alt="image" src="https://github.com/user-attachments/assets/13e883a3-d697-4880-9dfd-2167f9b0a8f2" />

500 ilgio simbolių poros

<img width="345" height="102" alt="image" src="https://github.com/user-attachments/assets/dac79630-5b53-4ca6-85fe-9f790b9f8a5b" />

1000 ilgio simbolių poros

<img width="349" height="103" alt="image" src="https://github.com/user-attachments/assets/4c3d6b58-93ac-4e44-80d8-ee526bc59d38" />

6. Lavinos efektas. Panaudojant penktą funkciją, gauname failo pasirinkimą kurio elementus hash'uos ir palygins poromis. Rezultatai panaudojant failą, kur elementai yra 100 simbolių ilgumo:

<img width="381" height="232" alt="image" src="https://github.com/user-attachments/assets/70c8d946-656c-4f65-b710-3009c16b7cdc" />

7. Negrįžtamumo demonstracija. Panaudojant šeštą funkciją, automatiškai parodo, kaip vienas hard-coded įvestis keičiasi priklausant nuo druskos.

<img width="509" height="167" alt="image" src="https://github.com/user-attachments/assets/67c934bc-3a78-41dc-922e-f364bfa952be" />


8. Išvados

(+) Veikia.

(+) Mažai kodo, lengvai skaitomas.

(+) Priima bet kokį simbolį.

(+) Visada tokio pačio dydžio išvestis.

(+) Deterministiška.

(+) Veikimas linijinis.

(-) Didelė tikimybė kolizijų, nes hash'as tik 64 bitų, matytusi su ~2^32 įvestims (galima nesunkiai praplėsti).

(+) Ypač gerai pasižymi lavinos efektu, nes pakeitus įvesti vienu simboliu hash'as labai stipriai skiriasi.

(+) Lengva įterpti druska.

(-) Hash'as ne kriptografiškas.

(-) Pirminių skaičių lentelė kartojasi kas 10 baitų, tai hash funkcijai gali pridėti nuspėjamumo.

# Palyginimas su SHA-256
My_hash vs SHA-256
+   Išvestis: 64-bit vs 256-bit.
+   Saugumas: Ne vs Taip.
+   Kolizijos atsparumas: Silpnas vs Labai stiprus.
+   Paprastumas: Paprastas vs Vidutinis.
+   Greitis: Priklauso nuo įvesties dydžio, su mažesnėm įvestim my_hash daro mažiau veiksmų ir dėl to greitesnis, bet su didesnėm įvestim SHA-256 greit susitapatina ir dar greičiau aplenkia pasitelkiant savo itin dideliu pralaidumu.
+   Tinkamas piknaudiškoms įvestims / Sunku atkurti veikimą: Ne vs Taip.
+   Žinomas: Ne vs Taip