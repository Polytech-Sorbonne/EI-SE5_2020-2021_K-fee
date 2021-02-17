# curl -X GET http://localhost:8000/Pieces
# curl -X POST http://localhost:8000/Pieces/\?Nom\=Bureau\&X\=1\&Y\=1\&Z\=1

import http.server, urllib.parse, sqlite3, threading
import paho.mqtt.client as mqtt
import socketserver,_thread
import json

MQTT_ADDRESS = '192.168.20.226'
MQTT_USER = 'mickael'
MQTT_PASSWORD = 'mickael'

class MyHandler(http.server.BaseHTTPRequestHandler):
	def __init__(self, *args, **kwargs):
		self.mysql = MySQL('k_fee.db')
		super(MyHandler, self).__init__(*args, **kwargs)

	def do_GET(self):
		"""Respond to a GET request."""
		print("GET" + self.path)
		if self.path == '/favicon.ico':
			return
		if self.path == '/' or self.path == '/pageAccueil.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageAccueil.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/script.js':
			self.send_response(200)
			self.send_header("Content-type", "text/js")
			self.end_headers()
			#ouverture en lecture
			f = open("script.js","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/pageRoutine.js':
			self.send_response(200)
			self.send_header("Content-type", "text/js")
			self.end_headers()
			#ouverture en lecture
			f = open("pageRoutine.js","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/pageCafe.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageCafe.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/pageHist.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageHist.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/pageRoutine.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageRoutine.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/pageChargAddRecette.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageChargAddRecette.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/pageRecette.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageRecette.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		elif self.path == '/pageChargSupRecette.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageChargSupRecette.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))


		elif self.path == '/GetRecette':
			#ouverture en lecture
			rep = self.mysql.selectRecette(self.path);
			#print(rep)
			res = '{'
			res += '"Recette" : ['
			for v in rep :
				res += v[0]
				res += ','
			res = res[:-1]
			res += ']}'
			#print(res)
			if len(rep) > 0 :
				self.send_response(200)
				self.send_header("Content-type", "text/json")
				self.end_headers()
				self.wfile.write(bytes(str(res)+'\n', 'UTF-8'))
			else:
				self.send_response(404)
				self.send_header("Content-type", "text/html")
				self.end_headers()

		elif self.path == '/GetRoutine':
			#ouverture en lecture
			rep = self.mysql.selectRoutine(self.path);
			print(rep)
			if len(rep) > 1 :
				res = '{'
				res += '"Routine" : ['
				for v in rep :
					res += v[0]
					res += ','
				res = res[:-1]
				res += ']}'
				print(res)
			elif len(rep) == 1 :
				res = '{'
				res += '"Routine" : '
				for v in rep :
					res += v[0]
					res += ','
				res = res[:-1]
				res += '}'
				print(res)

			if len(rep) > 0 :
				self.send_response(200)
				self.send_header("Content-type", "text/json")
				self.end_headers()
				self.wfile.write(bytes(str(res)+'\n', 'UTF-8'))
			else:
				self.send_response(404)
				self.send_header("Content-type", "text/html")
				self.end_headers()

		else :
			res = urllib.parse.urlparse(self.path)
			rep = self.mysql.select(res.path)
			print("res.path : ")
			print(res.path)
			if len(rep) > 0:
				self.send_response(200)
				self.send_header("Content-type", "text/html")
				self.end_headers()
				self.wfile.write(bytes(str(rep)+'\n', 'UTF-8'))
			else:
				self.send_response(404)
				self.send_header("Content-type", "text/html")
				self.end_headers()

	def do_POST(self):
		"""Respond to a POST request."""
		print("POST " + self.path)

		if self.path == '/CafeInstantane':
			res = self.rfile.read(int(self.headers['content-length'])).decode(encoding="utf-8")
			print(res)
			query = urllib.parse.parse_qs(res,keep_blank_values=1,encoding='utf-8')
			print(query)
			val ='1'
			for v in query.values() :
				if v[0] == "Grand" :
					val += '2'
				elif v[0] == "Petit" :
					val += "1"
				else :
					val += v[0]
			#print(val)
			#mqtt_client.publish("home/kfee",val)

			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()

		if self.path == '/pageChargAddRoutine.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageChargAddRoutine.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

			res = self.rfile.read(int(self.headers['content-length'])).decode(encoding="utf-8")
			#print(res)
			query = urllib.parse.parse_qs(res,keep_blank_values=1,encoding='utf-8')
			#print(query)
			dict = {}
			for key in query :
				if query[key] != [''] :
					dict[key] = query[key]
			print(dict)

			#######	Ajout d'une routine #######
			self.mysql.insertRoutine(dict['nom'])

			#######	Lundi #######
			if 'Lundi' in dict :
				self.mysql.insertJour('Lundi')
				id1 = self.mysql.selectRoutineID()
				id2 = self.mysql.selectJourID()
				self.mysql.insertPossede('Possede_RoutineJour',id1[0],id2[0])

				self.mysql.insertHeure(dict['heureLundi'])
				id1 = self.mysql.selectHeureID()
				self.mysql.insertPossede('Possede_JourHeure',id2[0],id1[0])

				id2 = self.mysql.selectRecetteID(dict['RecetteLundi'])
				self.mysql.insertPossede('Possede_HeureRecette',id1[0],id2[0])
			#######	Mardi #######
			if 'Mardi' in dict :
				self.mysql.insertJour('Mardi')
				id1 = self.mysql.selectRoutineID()
				id2 = self.mysql.selectJourID()
				self.mysql.insertPossede('Possede_RoutineJour',id1[0],id2[0])

				self.mysql.insertHeure(dict['heureLundi'])
				id1 = self.mysql.selectHeureID()
				self.mysql.insertPossede('Possede_JourHeure',id2[0],id1[0])

				id2 = self.mysql.selectRecetteID(dict['RecetteMardi'])
				self.mysql.insertPossede('Possede_HeureRecette',id1[0],id2[0])

			#######	Mercredi #######
			if 'Mercredi' in dict :
				self.mysql.insertJour('Mercredi')
				id1 = self.mysql.selectRoutineID()
				id2 = self.mysql.selectJourID()
				self.mysql.insertPossede('Possede_RoutineJour',id1[0],id2[0])

				self.mysql.insertHeure(dict['heureLundi'])
				id1 = self.mysql.selectHeureID()
				self.mysql.insertPossede('Possede_JourHeure',id2[0],id1[0])

				id2 = self.mysql.selectRecetteID(dict['RecetteMercredi'])
				self.mysql.insertPossede('Possede_HeureRecette',id1[0],id2[0])

			#######	Jeudi #######
			if 'Jeudi' in dict :
				self.mysql.insertJour('Jeudi')
				id1 = self.mysql.selectRoutineID()
				id2 = self.mysql.selectJourID()
				self.mysql.insertPossede('Possede_RoutineJour',id1[0],id2[0])

				self.mysql.insertHeure(dict['heureLundi'])
				id1 = self.mysql.selectHeureID()
				self.mysql.insertPossede('Possede_JourHeure',id2[0],id1[0])

				id2 = self.mysql.selectRecetteID(dict['RecetteJeudi'])
				self.mysql.insertPossede('Possede_HeureRecette',id1[0],id2[0])

			#######	Vendredi #######
			if 'Vendredi' in dict :
				self.mysql.insertJour('Vendredi')
				id1 = self.mysql.selectRoutineID()
				id2 = self.mysql.selectJourID()
				self.mysql.insertPossede('Possede_RoutineJour',id1[0],id2[0])

				self.mysql.insertHeure(dict['heureLundi'])
				id1 = self.mysql.selectHeureID()
				self.mysql.insertPossede('Possede_JourHeure',id2[0],id1[0])

				id2 = self.mysql.selectRecetteID(dict['RecetteVendredi'])
				self.mysql.insertPossede('Possede_HeureRecette',id1[0],id2[0])

			#######	Samedi #######
			if 'Samedi' in dict :
				self.mysql.insertJour('Samedi')
				id1 = self.mysql.selectRoutineID()
				id2 = self.mysql.selectJourID()
				self.mysql.insertPossede('Possede_RoutineJour',id1[0],id2[0])

				self.mysql.insertHeure(dict['heureLundi'])
				id1 = self.mysql.selectHeureID()
				self.mysql.insertPossede('Possede_JourHeure',id2[0],id1[0])

				id2 = self.mysql.selectRecetteID(dict['RecetteSamedi'])
				self.mysql.insertPossede('Possede_HeureRecette',id1[0],id2[0])

			#######	Samedi #######
			if 'Dimanche' in dict :
				self.mysql.insertJour('Dimanche')
				id1 = self.mysql.selectRoutineID()
				id2 = self.mysql.selectJourID()
				self.mysql.insertPossede('Possede_RoutineJour',id1[0],id2[0])

				self.mysql.insertHeure(dict['heureLundi'])
				id1 = self.mysql.selectHeureID()
				self.mysql.insertPossede('Possede_JourHeure',id2[0],id1[0])

				id2 = self.mysql.selectRecetteID(dict['RecetteDimanche'])
				self.mysql.insertPossede('Possede_HeureRecette',id1[0],id2[0])




			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()


		elif self.path == '/pageChargAddRecette.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageChargAddRecette.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

			res = self.rfile.read(int(self.headers['content-length'])).decode(encoding="utf-8")
			print(res)
			query = urllib.parse.parse_qs(res,keep_blank_values=1,encoding='utf-8')
			print(query)
			self.mysql.insert('/Recette',query)
			self.end_headers()

		elif self.path == '/pageChargSupRecette.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageChargSupRecette.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

			res = self.rfile.read(int(self.headers['content-length'])).decode(encoding="utf-8")
			print(res)
			query = urllib.parse.parse_qs(res,keep_blank_values=1,encoding='utf-8')
			print(query)
			self.mysql.deleteRecette(self.path,query)
			self.end_headers()

		elif self.path == '/pageChargSupRoutine.html':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageChargSupRoutine.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

			res = self.rfile.read(int(self.headers['content-length'])).decode(encoding="utf-8")
			print(res)
			query = urllib.parse.parse_qs(res,keep_blank_values=1,encoding='utf-8')
			print(query)
			self.mysql.deleteRoutine(self.path,query)
			self.end_headers()

		else:
			res = urllib.parse.urlparse(self.path)
			query = urllib.parse.parse_qs(res.query)
			rep = self.mysql.insert(res,query)
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()

class MySQL():
	def __init__(self, name):
		self.c = None
		self.req = None
		self.conn = sqlite3.connect(name)
		self.c = self.conn.cursor()

	def __exit__(self, exc_type, exc_value, traceback):
		self.conn.close()


	def select(self,path):
		elem = path.split('/')
		if len(elem) == 2:
			req = "select * from %s" %(elem[1])
		else:
			req = "select %s from %s where id=%s" %(elem[3],elem[1],elem[2])
		return self.c.execute(req).fetchall()


	def selectRecette(self,path):
		req = "SELECT JSON_OBJECT('id', id, 'nom', nom, 'nb_dose_cafe',nb_dose_cafe,'nb_dose_sucre',nb_dose_sucre,'taille',taille,'temperature',temperature) from RECETTE;"
		# req = "SELECT id as [Recette.id], nom as [Recette.nom], nb_dose_cafe as [Recette.nb_dose_cafe], nb_dose_sucre as [Recette.nb_dose_sucre], taille as [Recette.taille], temperature as [Recette.temperature] FROM Recette FOR JSON PATH, ROOT('Recette')"

		return self.c.execute(req).fetchall()

	def selectRoutine(self,path):
		req = "SELECT JSON_OBJECT('id', id, 'nom', nom, 'etat', etat) from ROUTINE;"
		return self.c.execute(req).fetchall()

	def selectRoutineID(self):
		req = "select MAX(id) FROM Routine"
		return self.c.execute(req).fetchall()

	def selectJourID(self):
		req = "select MAX(id) FROM Jour"
		return self.c.execute(req).fetchall()

	def selectHeureID(self):
		req = "select MAX(id) FROM Heure"
		return self.c.execute(req).fetchall()

	def selectRecetteID(self,nom):
		req = "select id from Recette where nom='%s'" %(nom[0])
		return self.c.execute(req).fetchall()


	def insert(self,path,query):
		print(query)
		attr = ', '.join(query.keys())
		val = ', '.join('"%s"' %v[0] for v in query.values())
		print(attr,val)
		req = "insert into %s (%s) values (%s)" %(path.split('/')[1], attr, val)
		print(req)
		self.c.execute(req)
		self.conn.commit()

	def insertRoutine(self,nom):
		req = "insert into Routine (nom,etat) values ('%s','inactif')" %(nom[0])
		print(req)
		self.c.execute(req)
		self.conn.commit()

	def insertJour(self,nom):
		req = "insert into Jour (nom) values ('%s')" %(nom)
		print(req)
		self.c.execute(req)
		self.conn.commit()

	def insertHeure(self,time):
		heure = time[0].split(':')[0]
		minute = time[0].split(':')[1]
		req = "insert into Heure (heure, minute) values (%s,%s)" %(heure,minute)
		print(req)
		self.c.execute(req)
		self.conn.commit()

	def insertPossede(self,path,id1,id2):
		val = '%s,%s'%(id1[0],id2[0])
		req = "insert into %s values (%s)" %(path, val)
		print(req)
		self.c.execute(req)
		self.conn.commit()

	def deleteRecette(self,path,query):
		print(query)
		val = ', '.join('"%s"' %v[0] for v in query.values())
		print(val)
		req = "DELETE FROM Recette where nom =  (%s)" %(val)
		print(req)
		self.c.execute(req)
		self.conn.commit()

	def deleteRoutine(self,path,query):
		print(query)
		val = ', '.join('"%s"' %v[0] for v in query.values())
		print(val)
		#Recupérer l'ID de la Routine à supprimer
		idRoutine = "SELECT id FROM Routine where nom =  (%s)" %(val)
		print(idRoutine)
		idRoutine = self.c.execute(idRoutine).fetchall()
		idRoutine = idRoutine[0][0]
		print(idRoutine)

		#Recupérer l'ID des Jours à supprimer
		idJour = "SELECT idJour FROM Possede_RoutineJour where idRoutine =  (%s)" %(idRoutine)
		print(idJour)
		idJour = self.c.execute(idJour).fetchall()
		idJour = idJour[:][0]
		print(idJour)

		#Recupérer l'ID des heures à supprimer
		idHeure = "SELECT idHeure FROM Possede_JourHeure where idJour =  (%s)" %(idJour)
		print(idHeure)
		idHeure = self.c.execute(idHeure).fetchall()
		idHeure = idHeure[0][0]
		print(idHeure)

		#Supprimer Possede_HeureRecette
		req = "DELETE FROM Possede_HeureRecette where idHeure =  (%s)" %(idHeure)
		print(req)
		self.c.execute(req)
		self.conn.commit()

		#Supprimer Possede_JourHeure
		req = "DELETE FROM Possede_JourHeure where idJour =  (%s)" %(idJour)
		print(req)
		self.c.execute(req)
		self.conn.commit()

		#Supprimer Heure
		req = "DELETE FROM Heure where id =  (%s)" %(idHeure)
		print(req)
		self.c.execute(req)
		self.conn.commit()

		#Supprimer Possede_RoutineJour
		req = "DELETE FROM Possede_RoutineJour where idRoutine =  (%s)" %(idRoutine)
		print(req)
		self.c.execute(req)
		self.conn.commit()

		#Supprimer Jour
		req = "DELETE FROM Jour where id =  (%s)" %(idJour)
		print(req)
		self.c.execute(req)
		self.conn.commit()

		#Supprimer la Routine
		req = "DELETE FROM Routine where nom =  (%s)" %(val)
		print(req)
		self.c.execute(req)
		self.conn.commit()



class ThreadingHTTPServer(socketserver.ThreadingMixIn, http.server.HTTPServer):
	pass

def serve_on_port(port):
	server = ThreadingHTTPServer(("0.0.0.0", port), MyHandler)
	server.serve_forever()

if __name__ == '__main__':
	# Mono connection
	server_class = http.server.HTTPServer
	httpd = server_class(("0.0.0.0", 8000), MyHandler)

	# mqtt_client = mqtt.Client()
	# mqtt_client.username_pw_set(MQTT_USER, MQTT_PASSWORD)
	# mqtt_client.connect(MQTT_ADDRESS, 1883)

	try:
	# Mono connection : méthode of the server object to process one or many requests
		httpd.serve_forever()
	except KeyboardInterrupt:
		pass
	#close the socket
	httpd.server_close()
