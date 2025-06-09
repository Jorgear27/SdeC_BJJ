// gcc -o copia_archivo copia_archivo.c

#include <stdlib.h>
#include <ctype.h>
// #include <stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#define BUFSIZE 512

void main(int argc, char const *argv[])
{
	// Variables locales
	// Descriptor de entrada, salida y # de bytes leidos.
	int fd_in, fd_out, n_read;

	// Espacio en memoria para guardar lo leído
	char buffer[BUFSIZE];

	// Abre archivo de entrada
	fd_in = open(argv[1], O_RDONLY);
	if (fd_in < 0){
		perror("open source file");
		exit(1);
	}

	// Crea archivo de salida
	// O_WRONLY Solo para escritura
	// O_CREAT Si no existe lo crea
	fd_out = open(argv[2], O_WRONLY|O_CREAT, 0751);
	if (fd_out <0){
		close(fd_out);
		perror("open destination file");
		exit(1);
	}

	// Lazo para transferir datos desde argv[1] a argv[2].
	while ((n_read = read(fd_in, buffer, BUFSIZE)) > 0) {
		// Lee BUFSIZE bytes del archivo vinculado al descriptor fd_in y los guarda en buffer.
		// n_read es la cantidad de bytes devueltos en la lectura. Puede ser menor que BUFSIZE 
		// también puede ser cero (EOF).-

		// printf("El numero de caracteres es= %d \nY el contenido es: %s \n",n_read, buffer);
		
		if (write(fd_out, buffer, n_read) < n_read){
			// write devuelve el # de bytes escritos y si es menor a los que se debieron escribir (n_read)
			// se considera que hubo un error.
			perror("write");
			close(fd_in);
			close(fd_out);
			exit(1);
		}
	}

	if (n_read < 0) {
		// Si el valor de bytes leídos en el read e -1, hugo algún error.
		perror("read");
		close(fd_in);
		close(fd_out);
		exit(0);
	}

}

