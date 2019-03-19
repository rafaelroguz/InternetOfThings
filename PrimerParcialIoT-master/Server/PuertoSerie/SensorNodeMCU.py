
import serial
import time
import datetime
import psycopg2

conn = psycopg2.connect("dbname=d94n6uerkees6n user=zwpbbcgrvahhnu password=168c5333561f5ad0e886534d747f10cb5888f9b48ceb4b37c79eb54125430990 host=ec2-54-235-90-0.compute-1.amazonaws.com")

cur = conn.cursor()
ser = serial.Serial("COM8", 9600)
ser.reset_input_buffer()
sql = "INSERT INTO temperatura (muestraTemp, fechaMuestra, horaMuestra) VALUES(%s, %s, %s)"

while (1):
    ts = time.time()
    fechaHora = datetime.datetime.fromtimestamp(ts)
    dato = ser.readline()
    if dato != "b''" and len(dato)== 7:
        val = (float(dato), str(fechaHora.date()),  str(fechaHora))
        cur.execute(sql, val)
        conn.commit()
        print(val)