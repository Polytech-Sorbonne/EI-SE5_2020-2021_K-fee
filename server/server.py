# curl -X GET http://localhost:8000/Pieces
# curl -X POST http://localhost:8000/Pieces/\?Nom\=Bureau\&X\=1\&Y\=1\&Z\=1

import http.server, urllib.parse, sqlite3, threading

import socketserver,_thread


class MyHandler(http.server.BaseHTTPRequestHandler):
	def __init__(self, *args, **kwargs):
		self.mysql = MySQL('logement.db')
		super(MyHandler, self).__init__(*args, **kwargs)

	def do_GET(self):
		"""Respond to a GET request."""
		print("GET" + self.path)
		if self.path == '/favicon.ico':
			return
		if self.path == '/':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageAccueil.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		# elif self.path == '/style1.css':
		# 	self.send_response(200)
		# 	self.send_header("Content-type", "text/css")
		# 	self.end_headers()
		# 	#ouverture en lecture
		# 	f = open("style1.css","r") #lecture
		# 	s = f.read()
		# 	self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))
		# elif self.path == '/interaction1.js':
		# 	self.send_response(200)
		# 	self.send_header("Content-type", "text/js")
		# 	self.end_headers()
		# 	#ouverture en lecture
		# 	f = open("interaction1.js","r") #lecture
		# 	s = f.read()
		# 	self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))


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

				###########################
				####### A MODIFIER ########
				###########################
	def do_POST(self):
		"""Respond to a POST request."""
		print("POST " + self.path)
		if self.path == "/index.html":
			res = self.rfile.read(int(self.headers['content-length'])).decode(encoding="utf-8")
			query = urllib.parse.parse_qs(res,keep_blank_values=1,encoding='utf-8')
			path = "/Etudiant"

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


	def insert(self,path,query):
		print(query)
		attr = ', '.join(query.keys())
		val = ', '.join('"%s"' %v[0] for v in query.values())
		print(attr,val)
		req = "insert into %s (%s) values (%s)" %(path.split('/')[1], attr, val)
		print(req)
		self.c.execute(req)
		self.conn.commit()

	def insertPossede(self,path,id1,id2):
		val = '%s,%s'%(id1,id2)
		print(val)
		req = "insert into %s values (%s)" %(path.split('/')[1], val)
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

	# Multiple connections
	# threading.Thread(target=serve_on_port, args=[7777]).start()
	# threading.Thread(target=serve_on_port, args=[8888]).start()

	try:
	# Mono connection : méthode of the server object to process one or many requests
		httpd.serve_forever()
	except KeyboardInterrupt:
		pass
	#close the socket
	httpd.server_close()
