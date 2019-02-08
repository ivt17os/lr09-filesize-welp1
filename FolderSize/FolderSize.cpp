// ПАВЛОВ АЛЕКСАНДР

#include <windows.h>
#include <stdio.h>
#include <TCHAR.h>
#pragma warning( disable : 4996)
 
static int count;
static long long size;
 


void dfs() {
    // начинает перебор файлов и папок в текущей папке
    // 1) папки . и	 .. пропускаем
    // 2) если папка, то заходим в нее и вызываем dfs
    // 3) если файл, то посчитаем его в суммах count и size
    // 4) выходим в родительскую папку
 
    HANDLE hFind;                   	// номер поиска
    WIN32_FIND_DATA res;            	// результат поиска
 
    hFind = FindFirstFile(L"*", &res);   // найти первый файл
 
do {

 
		if ((res.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0 
			&& _tcscmp(res.cFileName, TEXT("..")) != 0 
			&& _tcscmp(res.cFileName, TEXT(".")) != 0) { // åñëè ýòî ïîäïàïêà
				SetCurrentDirectory(res.cFileName);
				dfs();
				SetCurrentDirectory(TEXT(".."));
			//	çäåñü áóäåò îáõîä â ãëóáèíó
		}
         else {// ýòî ôàéë
			if (_tcscmp(res.cFileName, TEXT("..")) != 0
				&& _tcscmp(res.cFileName, TEXT("..")) != 0) count++;
			  count++; // íåêîòîðûå ôàéëû íå ñ÷èòàþòñÿ??
			 long long filesize;
			 filesize = res.nFileSizeHigh;
			 filesize = filesize << 32;
			 filesize = filesize + res.nFileSizeLow;	
		     size +=filesize;
			 _tprintf(TEXT("file #%d is <%s>\n"), count, res.cFileName);
         }
    } while (FindNextFile(hFind, &res) != 0);
    FindClose(hFind);
}
 
int main(int argc, wchar_t* argv[]) {
    wchar_t s[512];               	// текущая папка
    GetCurrentDirectory(512, s);  	// получить текущую папку
    wprintf(L"Starting in: %s\n", s);
 
    count = 0;                  	// обнулить счетчик файлов
    size = 0;                   	// обнулить суммарный размер файлов
    dfs();                      	// запустить обход в глубину из текущей папки
 
    printf("File count = %d, size = %lld\n", count, size);
    return 0;
}
 
