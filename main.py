import serial

from socketIO_client_nexus import SocketIO, BaseNamespace

class Namespace(BaseNamespace):
	def on_connect(self):
		print('[Connected]')

	def on_reconnect(self):
		print('[Reconnected]')

	def on_disconnect(self):
		print('[Disconnected]')

with SocketIO('192.168.43.22', 5000, Namespace) as socketIO:
	socketIO.emit('client-serial-event', None)
	socketIO.wait(seconds=1)

	while True:
		ser = serial.Serial('/dev/ttyACM1', 115200)
		line = ser.readline()
		decoded = line.decode('utf-8')
		socketIO.emit('data-from-serial', decoded)