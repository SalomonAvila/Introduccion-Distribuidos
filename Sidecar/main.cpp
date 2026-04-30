void tarea_hijo(int id) {  
	while (true) {  
    	std::cout << "Hijo " << id << " corriendo (PID: " << getpid() << ")\\n";  
    	sleep(2 * id);  
	}  
}  
 
int main() {  
	std::cout << "Proceso Padre Iniciado (PID: " << getpid() << ")\\n";  
 
	for (int i = 1; i <= 3; ++i) {  
    	pid_t pid = fork();  
 
    	if (pid < 0) {  
        	std::cerr << "Error al crear hijo\\n";  
        	return 1;  
    	} else if (pid == 0) {  
        	tarea_hijo(i);  
        	return 0;   
    	}  
	}  
 
	while (true) {  
    	std::cout << "Padre vigilando...\\n";  
    	sleep(10);  
	}  
 
	return 0;  
}  
