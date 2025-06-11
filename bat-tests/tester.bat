set program=Hierarchy_List_of_Headers.exe

echo 01 - Базовый тест > .\actual_outputs\result_1.txt
%program% .\inputs\01_basic.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_1.txt

echo 02 - Комплексный тест > .\actual_outputs\result_2.txt
%program% .\inputs\02_complex.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_2.txt

echo 03 - Тег body без заголовочных тегов > .\actual_outputs\result_3.txt
%program% .\inputs\03_bodyWithNoHeaders.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_3.txt

echo 04 - Первый заголовочный тег не h1 > .\actual_outputs\result_4.txt
%program% .\inputs\04_firstHeaderNotH1.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_4.txt

echo 05 - Пустой заголовочный тег > .\actual_outputs\result_5.txt
%program% .\inputs\05_emptyHeaderTag.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_5.txt

echo 06 - Несколько тегов h1 > .\actual_outputs\result_6.txt
%program% .\inputs\06_multipleH1.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_6.txt

echo 07 - Секция вложена в секцию > .\actual_outputs\result_7.txt
%program% .\inputs\07_sectionInSection.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_7.txt

echo 08 - Пропущен уровень в последовательности > .\actual_outputs\result_8.txt
%program% .\inputs\08_skipLevel.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_8.txt

echo 09 - Заголовочный тег содержит другие теги > .\actual_outputs\result_9.txt
%program% .\inputs\09_headerContainsOtherTags.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_9.txt

echo 10 - Первый заголовочный тег в секции не h1 > .\actual_outputs\result_10.txt
%program% .\inputs\10_firstHeaderInSectionNotH1.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_10.txt

echo 11 - Несколько h1 в секции > .\actual_outputs\result_11.txt
%program% .\inputs\11_multipleH1inSection.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_11.txt

echo 12 - Корректное использование секций > .\actual_outputs\result_12.txt
%program% .\inputs\12_correctSectionAndArticle.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_12.txt

echo 13 - Большая корректная вложенность > .\actual_outputs\result_13.txt
%program% .\inputs\13_deepCorrectNesting.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_13.txt

echo 14 - Необычный текст внутри заголовочного тега > .\actual_outputs\result_14.txt
%program% .\inputs\14_uncommonTextInsideHeader.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_14.txt

echo 15 - Обратный порядок заголовков > .\actual_outputs\result_15.txt
%program% .\inputs\15_reversedOrderOfHeaders.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_15.txt

echo 16 - Комплексный тест номер 2 > .\actual_outputs\result_16.txt
%program% .\inputs\16_complexTestNumber2.html .\actual_outputs\tmp.txt
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_16.txt

del .\actual_outputs\tmp.txt