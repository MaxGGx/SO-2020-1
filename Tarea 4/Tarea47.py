import threading
import time
from datetime import datetime,timedelta
########################################>DECLARACION DE LAS VARIABLES PARA ALMACENAR LAS THREADS Y LAS LINEAS DE TEXTO PARA EL TXT<########################################
########################################>JUNTO CON LA VARIABLE PARA EL BAÑO Y LAS QUE SON GLOBALES EN EL CÓDIGO<########################################
textos = []
textoscajas = []
threads=[]
threadsc=[]
banio = 0
global flag
global aa
global bb
global cc
global dd
global ee
global aaa
global bbb
global ccc
global ddd
global eee

def Entrada(n):
	global textos
	semaforoIn.acquire()
	textos.append("Cliente N°: "+str(n)+" entró a la tienda a las "+str(datetime.now().time())+"\n")
	time.sleep(4)
	textos.append("Cliente N°: "+str(n)+" terminó de elegir productos a las "+str(datetime.now().time())+"\n")

def Cajas(n):
	global aa
	global bb
	global cc
	global dd
	global ee
	global aaa
	global bbb
	global ccc
	global ddd
	global eee
	global textos
	while(True):
		########################################>PARA - CAJERO 1<########################################
		if not lock11.locked():	
			if aa == 1:
				lock11.acquire()
				aa = 0
				lock11.release()
				semaforoC1.acquire()
				textos.append("Cliente N°: "+str(n)+" entró a la Caja 1 a las "+str(datetime.now().time())+"\n")
				aaa = n
				time.sleep(5)
				semaforoC1.release()
				s1.set()
				textos.append("Cliente N°: "+str(n)+" salió de la Caja 1 y la tienda a las "+str(datetime.now().time())+"\n")
				semaforoIn.release()
				return 0
			
		########################################>PARA - CAJERO 2<########################################
		if not lock22.locked():
			if bb == 1:
				lock22.acquire()
				bb = 0
				lock22.release()
				semaforoC2.acquire()
				textos.append("Cliente N°: "+str(n)+" entró a la Caja 2 a las "+str(datetime.now().time())+"\n")
				bbb=n
				time.sleep(5)
				semaforoC2.release()
				s2.set()
				textos.append("Cliente N°: "+str(n)+" salió de la Caja 2 y la tienda a las "+str(datetime.now().time())+"\n")
				semaforoIn.release()
				return 0
			
		########################################>PARA - CAJERO 3<########################################
		if not lock33.locked():
			if cc == 1:
				lock33.acquire()
				cc = 0
				lock33.release()
				semaforoC3.acquire()
				textos.append("Cliente N°: "+str(n)+" entró a la Caja 3 a las "+str(datetime.now().time())+"\n")
				ccc=n
				time.sleep(5)
				semaforoC3.release()
				s3.set()
				textos.append("Cliente N°: "+str(n)+" salió de la Caja 3 y la tienda a las "+str(datetime.now().time())+"\n")
				semaforoIn.release()
				return 0
			
		########################################>PARA - CAJERO 4<########################################
		if not lock44.locked():
			if dd == 1:
				lock44.acquire()
				dd = 0
				lock44.release()
				semaforoC4.acquire()
				textos.append("Cliente N°: "+str(n)+" entró a la Caja 4 a las "+str(datetime.now().time())+"\n")
				ddd=n
				time.sleep(5)
				semaforoC4.release()
				s4.set()
				textos.append("Cliente N°: "+str(n)+" salió de la Caja 4 y la tienda a las "+str(datetime.now().time())+"\n")
				semaforoIn.release()
				return 0
			
		########################################>PARA - CAJERO 5<########################################
		if not lock55.locked():	
			if ee == 1:
				lock55.acquire()
				ee = 0
				lock55.release()
				semaforoC5.acquire()
				textos.append("Cliente N°: "+str(n)+" entró a la Caja 5 a las "+str(datetime.now().time())+"\n")
				eee=n
				time.sleep(5)
				semaforoC5.release()
				s5.set()
				textos.append("Cliente N°: "+str(n)+" salió de la Caja 5 y la tienda a las "+str(datetime.now().time())+"\n")
				semaforoIn.release()
				return 0 
		#################################################################################################

def Cajeros(n):
	global aa
	global bb
	global cc
	global dd
	global ee
	global aaa
	global bbb
	global ccc
	global ddd
	global eee
	global textoscajas
	global flag
	global banio
	########################################>CAJERO 1<########################################
	if n==1: 
		a = 0
		while(True):
			if flag:
				break
			else:
				lock11.acquire()
				aa = 1
				lock11.release()
				s1.wait()
				if flag:
					break
				textoscajas.append("Cajero N°: "+str(n)+" atendió al cliente N° "+str(aaa)+" a las "+str((datetime.now()-timedelta(seconds=5)).time())+"\n")
				a+=1
				lock.acquire()
				if banio == 0 and a==5:
					banio = 1
					lock.release()
					textoscajas.append("Cajero N°: "+str(n)+" fue al baño a las "+str(datetime.now().time())+"\n")
					time.sleep(4)
					lock.acquire()
					banio = 0
					lock.release()
					s1.clear()
					a=0
					textoscajas.append("Cajero N°: "+str(n)+" salió del baño a las "+str(datetime.now().time())+"\n")
				elif banio==1 and a==5:
					lock.release()
					s1.clear()
					a=4
				else:
					lock.release()
					s1.clear()
		return 0
	########################################>CAJERO 2<########################################
	if n==2:
		b = 0
		while(True):
			if flag:
				break
			else:
				lock22.acquire()
				bb = 1
				lock22.release()
				s2.wait()
				if flag:
					break
				textoscajas.append("Cajero N°: "+str(n)+" atendió al cliente N° "+str(bbb)+" a las "+str((datetime.now() - timedelta(seconds=5)).time())+"\n")
				b+=1
				lock.acquire()
				if banio == 0 and b==5:
					banio = 1
					lock.release()
					textoscajas.append("Cajero N°: "+str(n)+" fue al baño a las "+str(datetime.now().time())+"\n")
					time.sleep(4)
					lock.acquire()
					banio = 0
					lock.release()
					s2.clear()
					b=0
					textoscajas.append("Cajero N°: "+str(n)+" salió del baño a las "+str(datetime.now().time())+"\n")
				elif banio==1 and b==5:
					lock.release()
					s2.clear()
					b=4
				else:
					lock.release()
					s2.clear()
		return 0
	########################################>CAJERO 3<########################################
	if n==3:
		c = 0
		while(True):
			if flag:
				break
			else:
				lock33.acquire()
				cc = 1
				lock33.release()
				s3.wait()
				if flag:
					break
				textoscajas.append("Cajero N°: "+str(n)+" atendió al cliente N° "+str(ccc)+" a las "+str((datetime.now()-timedelta(seconds=5)).time())+"\n")
				c+=1
				lock.acquire()
				if banio == 0 and c==5:
					banio = 1
					lock.release()
					textoscajas.append("Cajero N°: "+str(n)+" fue al baño a las "+str(datetime.now().time())+"\n")
					time.sleep(4)
					lock.acquire()
					banio = 0
					lock.release()
					s3.clear()
					c=0
					textoscajas.append("Cajero N°: "+str(n)+" salió del baño a las "+str(datetime.now().time())+"\n")
				elif banio == 1 and c==5:
					lock.release()
					s3.clear()
					c=4
				else:
					lock.release()
					s3.clear()
		return 0
	########################################>CAJERO 4<########################################
	if n==4:
		d = 0
		while(True):
			if flag:
				break
			else:
				lock44.acquire()
				dd = 1
				lock44.release()
				s4.wait()
				if flag:
					break
				textoscajas.append("Cajero N°: "+str(n)+" atendió al cliente N° "+str(ddd)+" a las "+str((datetime.now()-timedelta(seconds=5)).time())+"\n")
				d+=1
				lock.acquire()
				if banio == 0 and d==5:
					banio = 1
					lock.release()
					textoscajas.append("Cajero N°: "+str(n)+" fue al baño a las "+str(datetime.now().time())+"\n")
					time.sleep(4)
					lock.acquire()
					banio = 0
					lock.release()
					s3.clear()
					d=0
					textoscajas.append("Cajero N°: "+str(n)+" salió del baño a las "+str(datetime.now().time())+"\n")
				elif banio == 1 and d==5:
					lock.release()
					s4.clear()
					d=4
				else:
					lock.release()
					s4.clear()
		return 0
	########################################>CAJERO 5<########################################
	if n==5:
		e = 0
		while(True):
			if flag:
				break
			else:
				lock55.acquire()
				ee = 1
				lock55.release()
				s5.wait()
				if flag:
					break
				textoscajas.append("Cajero N°: "+str(n)+" atendió al cliente N° "+str(eee)+" a las "+str((datetime.now()-timedelta(seconds=5)).time())+"\n")
				e+=1
				lock.acquire()
				if banio == 0 and e==5:
					banio = 1
					lock.release()
					textoscajas.append("Cajero N°: "+str(n)+" fue al baño a las "+str(datetime.now().time())+"\n")
					time.sleep(4)
					lock.acquire()
					banio = 0
					lock.release()
					s5.clear()
					e=0
					textoscajas.append("Cajero N°: "+str(n)+" salió del baño a las "+str(datetime.now().time())+"\n")
				elif banio==1 and e==5:
					lock.release()
					s5.clear()
					e=4
				else:
					lock.release()
					s5.clear()
		return 0
########################################>FUNCION QUE JUNTA LAS DOS PARA CLIENTE<########################################
def Supermercado(n):
	Entrada(n)
	Cajas(n)
########################################>MAIN THREAD<########################################
if __name__ == '__main__':
########################################>DECLARACION DE SEMÁFOROS<########################################
	semaforoIn = threading.BoundedSemaphore(30)
	semaforoC1 = threading.BoundedSemaphore(1)
	semaforoC2 = threading.BoundedSemaphore(1)
	semaforoC3 = threading.BoundedSemaphore(1)
	semaforoC4 = threading.BoundedSemaphore(1)
	semaforoC5 = threading.BoundedSemaphore(1)
########################################>DECLARACIONES DE VALORES PARA VARIABLES GLOBALES<########################################
	aa = 0
	bb = 0
	cc = 0
	dd = 0
	ee = 0
########################################>DECLARACIONES PARA LOCKS DE CAJEROS Y EL DE BANIO<########################################
	lock = threading.Lock()
	lock11 = threading.Lock()
	lock22 = threading.Lock()
	lock33 = threading.Lock()
	lock44 = threading.Lock()
	lock55 = threading.Lock()
########################################>DECLARACIONES DE EVENTOS PARA LOS CAJEROS<########################################
	s1 = threading.Event()
	s2 = threading.Event()
	s3 = threading.Event()
	s4 = threading.Event()
	s5 = threading.Event()
########################################>DECLARACION DE FLAG PARA CAJEROS<########################################
	flag = False
########################################>INPUT DE CLIENTES (THREADS) A CREAR<########################################
	ctes = int(input("Indique la cantidad de clientes: "))
########################################>CREACION E INSERCIÓN DE CAJEROS A SUS PUESTOS<########################################
	for i in range(1,6,1):
		t = threading.Thread(target=Cajeros, args=(i,))
		threadsc.append(t)
		t.start()
########################################>CREACION E INSERCIÓN DE CLIENTES AL SUPERMERCADO<########################################
	for i in range(ctes):
		t = threading.Thread(target=Supermercado, args=(i,))
		threads.append(t)
		t.start()
########################################>JOIN PARA LOS CLIENTES<########################################
	for t in threads:
		t.join()
########################################>AVISO DE FINALIZACION PARA LOS CAJEROS<########################################
	flag = True
	s1.set()
	s2.set()
	s3.set()
	s4.set()
	s5.set()
########################################>JOIN PARA LOS CAJEROS<########################################
	for t in threadsc:
		t.join()
########################################>CREACION Y TRASPASO DE LA INFORMACION DE CLIENTES Y CAJEROS A SUS TXT<########################################
	Clientes = open("clientes.txt", "w")
	for x in textos:
		Clientes.write(x)
	Clientes.close()
	
	Cajas = open("cajeros.txt", "w")
	for x in textoscajas:
		Cajas.write(x)
	Cajas.close()
########################################>PRINT PARA PODER CORROBORAR LA FINALIZACIÓN DEL PROGRAMA<########################################
print('------------------------Finalizado------------------------')