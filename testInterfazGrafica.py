import tkinter as tk
from tkinter import messagebox, ttk
from tkinter import *

# Funciones para los botones
def accion1():
    messagebox.showinfo("Acción 1", "¡Botón 1 presionado!")

def accion2():
    messagebox.showinfo("Acción 2", "¡Botón 2 presionado!")

# Crear la ventana principal
root = tk.Tk()
root.title("Interfaz con Botones")

# Crear los botones
boton1 = ttk.Button(root, text="Botón 1 (A)", command=accion1)
boton2 = ttk.Button(root, text="Botón 2 (B)", command=accion2)

# Posicionar los botones
boton1.grid(row=0, column=0, padx=10, pady=10)
boton2.grid(row=0, column=1, padx=10, pady=10)

# Asociar teclas de atajo
root.bind("<KeyPress-a>", lambda e: accion1())
root.bind("<KeyPress-b>", lambda e: accion2())

# Iniciar la aplicación
root.mainloop()
