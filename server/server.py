# curl -X GET http://localhost:8888/Etudiant
# curl -X POST http://localhost:8888/Etudiant/\?Nom\=Cionaire\&Prenom\=Dick\&idAd\=2

import http.server, urllib.parse, sqlite3

class MyHandler(http.server.BaseHTTPRequestHandler):
	def __init__(self, *args, **kwargs):
		self.mysql = MySQL('k_fee.db')
		super(MyHandler, self).__init__(*args, **kwargs)

	def do_GET(self):
		"""Respond to a GET request."""
		res = urllib.parse.urlparse(self.path)
		rep = self.mysql.select(res.path)

		if self.path == '/':
			self.send_response(200)
			self.send_header("Content-type", "text/html")
			self.end_headers()
			#ouverture en lecture
			f = open("pageAccueil.html","r") #lecture
			s = f.read()
			self.wfile.write(bytes(str(s)+'\n', 'UTF-8'))

		else:
			self.send_response(404)
			self.send_header("Content-type", "text/html")
			self.end_headers()

	def do_POST(self):
		"""Respond to a POST request."""
		res = urllib.parse.urlparse(self.path)
		query = urllib.parse.parse_qs(res.query)
		rep = self.mysql.insert(res.path,query)
		self.send_response(200)
		self.send_header("Content-type", "text/html")
		self.end_headers()

		# if self.path == '/Factures.html':
		# 	res = self.rfile.read(int(self.headers['content-length'])).decode(encoding="utf-8")
		# 	print(res)
		# 	query = urllib.parse.parse_qs(res,keep_blank_values=1,encoding='utf-8')
		# 	print(query)
		# 	path = "/Factures"
		# 	rep = self.mysql.insert(path,query)
		# 	self.send_response(200)
		# 	self.send_header("Content-type", "text/html")
		# 	self.end_headers()

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

if __name__ == '__main__':
	server_class = http.server.HTTPServer
	httpd = server_class(("localhost", 8888), MyHandler)
	try:
		httpd.serve_forever()
	except KeyboardInterrupt:
		pass
	httpd.server_close()
