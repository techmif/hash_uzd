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
