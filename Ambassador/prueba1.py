import subprocess

url = "http://192.168.49.2:32694/"
intentos = 20

print(f"--- Iniciando 10 ráfagas de curl a {url} ---\n")

for i in range(1, intentos + 1):
    print(f"Solicitud #{i}:")
    
    # Ejecutamos curl -s (silent) para que no muestre la barra de progreso
    resultado = subprocess.run(["curl", "-s", url], capture_output=True, text=True)
    
    if resultado.returncode == 0:
        # Imprime la salida del servidor
        print(resultado.stdout)
    else:
        # Imprime el error si algo sale mal
        print(f"Error en el comando: {resultado.stderr}")
    
    print("-" * 30)

print("\n¡Listo! Todas las peticiones completadas.")
