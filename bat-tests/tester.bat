set program=Hierarchy_List_of_Headers.exe
set path=D:\Hierarchy_List_of_Headers\bat-tests

echo 01 - Базовый тест > %path%\actual_outputs\result_1.txt
%path%\%program% %path%\inputs\01_basic.html %path%\actual_outputs\tmp.txt 
type %path%\actual_outputs\tmp.txt >> %path%\actual_outputs\result_1.txt 


echo 02 - Комплексный тест > %path%\actual_outputs\result_2.txt
%program% %path%\inputs\02_complex.html %path%\out\result_2.txt > %path%\actual_outputs\tmp.txt 2>&1
type %path%\actual_outputs\tmp.txt >> %path%\actual_outputs\result_2.txt


echo 03 - Пустой тег body > .\actual_outputs\result_3.txt
%program% .\inputs\03_emptyBody.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_3.txt


echo 04 - Тег body без заголовочных тегов > .\actual_outputs\result_4.txt
%program% .\inputs\04_bodyWithNoHeaders.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_4.txt


echo 05 - Первый заголовочный тег не h1 > .\actual_outputs\result_5.txt
%program% .\inputs\05_firstHeaderNotH1.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_5.txt


echo 06 - Пустой заголовочный тег > .\actual_outputs\result_6.txt
%program% .\inputs\06_emptyHeaderTag.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_6.txt


echo 07 - Несколько h1 > .\actual_outputs\result_7.txt
%program% .\inputs\07_multipleH1.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_7.txt


echo 08 - section внутри section > .\actual_outputs\result_8.txt
%program% .\inputs\08_sectionInSection.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_8.txt


echo 09 - article внутри article > .\actual_outputs\result_9.txt
%program% .\inputs\09_articleInArticle.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_9.txt


echo 10 - section внутри article > .\actual_outputs\result_10.txt
%program% .\inputs\10_sectionInArticle.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_10.txt


echo 11 - article внутри section > .\actual_outputs\result_11.txt
%program% .\inputs\11_articleInSection.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_11.txt 


echo 12 - Пропущен один уровень в последовательности > .\actual_outputs\result_12.txt
%program% .\inputs\12_skipLevel.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_12.txt


echo 13 - Заголовочный тег содержит другие теги > .\actual_outputs\result_13.txt
%program% .\inputs\13_headerContainsOtherTags.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_13.txt


echo 14 - Первый заголовочный тег в section не h1 > .\actual_outputs\result_14.txt
%program% .\inputs\14_firstHeaderInSectionNotH1.html .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_14.txt


echo 15 - Первый заголовочный тег в article не h1 > .\actual_outputs\result_15.txt
%program% .\inputs\15_firstHeaderInArticleNotH1 .\actual_outputs\tmp.txt 
type .\actual_outputs\tmp.txt >> .\actual_outputs\result_15.txt


del %path%\actual_outputs\tmp.txt