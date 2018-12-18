#include<stdio.h>
#include <conio.h>
#include <string.h>

void readSinopsis(), readFilm(), readJadwal();

int main(){
	char Film[4][40], Jadwal[4][4][10];
	char seat[8][9];
	char Sinopsis[4][90];
	
	readFilm(Film);
	readJadwal(Jadwal);
	readSinopsis(Sinopsis);
	
	int filmpil = 99, jadwalpil = 99;
	char seatpil[3];
	seatpil[0]='X';
	
	printf("%s%c%c\n", "Content-Type:text/html;charset=iso-8859-1",13,10);
	
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
		case 's' :
			sscanf(data,"seat=%s", seatpil);
			break;
		default:
			break;
	}
	
	//Page_Control
	if (filmpil==99&&jadwalpil==99&&seatpil[0]=='X') pilihFilm(Film, Sinopsis, Jadwal);
		else if (jadwalpil==99&&seatpil[0]=='X') pilihJadwal(filmpil, Jadwal);
			else if (seatpil[0]=='X') pilihSeat(jadwalpil, seat);
				else cetak(seatpil, Film, Jadwal);
}

void pilihFilm(char Film[][40], char Sinopsis[][90], char Jadwal[][4][10]){	//sama dengan listFilm
	int i,j;
	printf("<head><link rel=\"stylesheet\" href=\"styles.css\"></head>");
	printf("<body>");
	printf("<div class=\"header\"><h1>Ini Aplikasi mesen tiket</h1><h2>Buy Tiket</h2></div>");
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
	printf("<head><link rel=\"stylesheet\" href=\"styles.css\"></head>");
	printf("<body>");
	printf("<div class=\"header\"><h1>Ini Aplikasi mesen tiket</h1><h2>Buy Tiket</h2></div>");
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

void pilihSeat(int jadwalpil, char seat[8][9]){
	readSeat(seat);
	int i,j;
	char baris[8] = "ABCDEFGH";
	char kolom[8] = "12345678";
	printf("<head><link rel=\"stylesheet\" href=\"styles.css\"></head>");
	printf("<body>");
	printf("<div class=\"header\"><h1>Ini Aplikasi mesen tiket</h1><h2>Buy Tiket</h2></div>");
	printf("<div class=\"seat\">");
	printf("<div><h3>Pilihan Kursi</h3>");
	printf("<form action=\"index.cgi\">");
		for(i=0;i<8;i++){
			for(j=0;j<8;j++){
				printf("<input type=\"radio\" name=\"seat\" value=\"%c%c\">%c%c</input>", baris[i], kolom[j], baris[i], kolom[j]);
			}
			printf("</br>");
		}
	printf("</div><div><input type=\"submit\" value=\"Submit!\"></div></form></div></body>");
	printf("</div>");

	int filmpil;
	FILE *fptr;
		fptr = fopen("tcache.txt","r+");
		//keramat: teks dimasukkan tidak mengoverwrite teks sebelumnya!
		fscanf(fptr,"%d", &filmpil);
		fprintf(fptr," %d", jadwalpil);
		//keramat
		fclose(fptr);
}
void cetak(char seatpil[3], char Film[][40], char Jadwal[][4][10]){
	
	struct summ {
		int filmpil;
		int jadwalpil;
		char seatpil[3];
	};
	
	struct summ summ1;
	strcpy(summ1.seatpil,seatpil);
	
	FILE *fptr;
		fptr = fopen("tcache.txt","r");
		fscanf(fptr,"%d %d", &summ1.filmpil, &summ1.jadwalpil);
		fclose(fptr);
	printf("<head> <title>Summary</title><link href='https://fonts.googleapis.com/css?family=Lobster|Kreon:400,700' rel='stylesheet' type='text/css'><link rel=\"stylesheet\" href=\"tiket.css\" media=\"screen\" charset=\"utf-8\"/> <meta content=\"width=device-width, initial-scale=1.0\" name=\"viewport\"><meta http-equiv=\"content-type\" content=\"text-html; charset=utf-8\"></head>");
	printf("<body><div class=\"container\"><section><div class=\"circle\"><div class=\"event\">Bioskop</br>kampus</div><div class=\"title\">UI!</div></div><div class=\"special\"></div><div class=\"special\"></div><div class=\"special\"></div><div class=\"special\"></div><div class=\"special\"><div class=\"seats\">");
	          printf("<span class=\"label\">Jam:</span><span> %s</span>", Jadwal[summ1.filmpil][summ1.jadwalpil]);
	printf("</div>");
	
			  printf("%s", Film[summ1.filmpil]);
	printf("</div><div class=\"special\"><div class=\"seats\"><span class=\"label\">");
			  printf("Seat: %s", seatpil);
	printf("</span><span></span></div>PUSAT KOMPUTER, FTUI</div></section><aside>");
		 printf("<img src=\"%d.jpeg\">",summ1.filmpil);
	printf("</aside></div></body>");
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

void readSeat(char input[8][9]){
	int i= 0;
	int k;
	FILE *ptrfile;
	
	ptrfile = fopen("kursi.txt","r");

	while(!feof(ptrfile))
	{
		if(fgets(input[i], 12, ptrfile) != NULL)
		{
			input[i][strcspn(input[i], "\n")] = 0;
			i++;
		}
	}	
	fclose(ptrfile);
}
