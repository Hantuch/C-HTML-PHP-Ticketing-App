#include<stdio.h>
#include <conio.h>
#include <string.h>

void readSinopsis(), readFilm(), readJadwal();

int main(){
	char Film[4][40], Jadwal[4][4][10];
	char Sinopsis[4][90];
	
	readFilm(Film);
	readJadwal(Jadwal);
	readSinopsis(Sinopsis);
	
	int filmpil = 99, jadwalpil = 99, jumlahtiket =99;
	
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	printf("<head><link rel=\"stylesheet\" href=\"styles.css\"></head>");
	printf("<body>");
	printf("<div class=\"header\"><h1>Ini Aplikasi mesen tiket</h1><h2>Buy Tiket</h2></div>");
	
	char *data;
	data = getenv("QUERY_STRING");
	
	//Input_Control
	switch(data[0]){
		case 'f' :
			sscanf(data,"film=%d",&filmpil);
			break;
		case 'j' :
			sscanf(data,"jadwal=%d",&jadwalpil);
			break;
		default:
			break;
	}
	
	//Page_Control
	if (filmpil==99&&jadwalpil==99) pilihFilm(Film, Sinopsis, Jadwal);
		else if (jadwalpil==99) pilihJadwal(filmpil, Jadwal);
				else cetak(jadwalpil, Film, Jadwal);
}

void pilihFilm(char Film[][40], char Sinopsis[][90], char Jadwal[][4][10]){	//sama dengan listFilm
	int i,j;
	printf("<div class=\"film\">");
	printf("<div><h3>Film Hari ini</h3>");
	printf("<form action=\"index.cgi\">");
	for(i=0;i<4;i++){
		printf("<div class=\"contFilm\">");
			printf("<img src=\"%d.jpeg\"></br>", i);
			printf("<input type=\"radio\" name=\"film\" value=\"%d\">%s</input></br>\n", i, Film[i]); 
			printf("<div>%s</div>", Sinopsis[i]);
			printf("Tersedia pukul: ");
			for(j=0;j<4;j++){
				printf("%s ", Jadwal[i][j]);
			}
		printf("</div>");	
	}
	printf("</div><div><input type=\"submit\" value=\"Submit!\"></div></form></div></body>");
	printf("</div>");
}

void pilihJadwal(int filmpil, char jadwal[][4][10]){		//sama dengan listJadwal
	int i;
	printf("<div class=\"jadwal\">");
	printf("<div><h3>Jadwal Film</h3>");
	printf("<form action=\"index.cgi\">");
	for(i=0;i<4;i++){
		printf("<input type=\"radio\" name=\"jadwal\" value=\"%d\">%s</input></br>\n", i, jadwal[filmpil][i]);
	}
	printf("</div><div><input type=\"submit\" value=\"Submit!\"></div></form></div></body>");
	printf("</div>");
	FILE *fptr;
		fptr = fopen("tcache.txt","w");
		//teks mengoverwrite teks sebelumnya
		fprintf(fptr,"%d", filmpil);
		fclose(fptr);
}

void cetak(int jadwalpil, char Film[][40], char Jadwal[][4][10]){
	
	struct summ {
		int filmpil;
		int jadwalpil;
	};
	
	struct summ summ1;
	summ1.jadwalpil=jadwalpil;
	
	FILE *fptr;
		fptr = fopen("tcache.txt","r");
		fscanf(fptr,"%d", &summ1.filmpil);
		fclose(fptr);
	printf("<div class=\"summary\">");
	printf("<h1>Summary</h1>");
	printf("<div><img src=\"%d.jpeg\"></div>", summ1.filmpil);
	printf("<P>Film Pilihan: %s </br> Jam: %s</P>", Film[summ1.filmpil], Jadwal[summ1.filmpil][summ1.jadwalpil]);
	printf("</div>");
}
/*
----------------------------------
|B A G I A N   B A C A - B A C A |
----------------------------------
*/

void readFilm(char input[][40])
{
	int i= 0;
	FILE *ptrfile;
	
	ptrfile = fopen("ListFilm.txt","r");

	while(!feof(ptrfile))
	{
		if(fgets(input[i], 40, ptrfile) != NULL)
		{
			input[i][strcspn(input[i], "\n")] = 0;
			i++;
		}
	}	
	fclose(ptrfile);
}

void readJadwal(char input[][4][10])
{
	int i= 0;
	int j;
	FILE *ptrfile;
	char temp[4][40];
	
	ptrfile = fopen("Jadwal.txt","r");

	while(!feof(ptrfile))
	{
		if(fgets(temp[i], 40, ptrfile) != NULL)
		{
			temp[i][strcspn(temp[i], "\n")] = 0;
			i++;
		}
	}	
	fclose(ptrfile);
	
	for(i=0;i<4;i++)
	{
		j = 0;
		sscanf(temp[i], "%s %s %s %s", &input[i][j], &input[i][j+1], &input[i][j+2], &input[i][j+3]);
	}
}

void readSinopsis(char input[][90])
{
	int j= 0;
	FILE *ptrfile;
	
	ptrfile = fopen("Sinopsis.txt","r");

	while(!feof(ptrfile))
	{
		if(fgets(input[j], 90, ptrfile) != NULL)
		{
			input[j][strcspn(input[j], "\n")] = 0;
			j++;
		}
	}	
	fclose(ptrfile);
}
