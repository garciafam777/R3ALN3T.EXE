import tkinter as tk
from tkinter import ttk, messagebox
import os
import csv
import random
from generate_netp import load_source_characters, generate_card, HEADERS, SOURCE_FILE, OUTPUT_FILE

class R3ALN3T_Console:
    def __init__(self, root):
        self.root = root
        self.root.title("R3ALN3T.EXE // DATA MATRIX GENERATOR")
        self.root.geometry("620x450")
        self.root.resizable(False, False)
        
        self.bg_color = "#0B0214"       
        self.frame_bg = "#160829"       
        self.accent_color = "#A855F7"   
        self.text_color = "#E9D5FF"     
        self.btn_bg = "#4C1D95"         

        self.root.configure(bg=self.bg_color)
        
        self.style = ttk.Style()
        self.style.theme_use("clam")
        self.style.configure(".", background=self.frame_bg, foreground=self.text_color)
        self.style.configure("TLabel", background=self.frame_bg, foreground=self.text_color, font=("Consolas", 10))
        self.style.configure("TEntry", fieldbackground="#24143D", foreground="#FFFFFF", insertcolor="#FFFFFF")
        
        self.build_ui()
        self.check_source_status()

    def build_ui(self):
        header_frame = tk.Frame(self.root, bg=self.bg_color)
        header_frame.pack(fill=tk.X, padx=20, pady=15)
        
        title_lbl = tk.Label(header_frame, text="R3ALN3T.EXE", font=("Consolas", 18, "bold"), fg=self.accent_color, bg=self.bg_color)
        title_lbl.pack(anchor=tk.W)
        subtitle_lbl = tk.Label(header_frame, text="NetP COMPILATION UTILITY // SYSTEM BUILD 3026", font=("Consolas", 9), fg="#7C3AED", bg=self.bg_color)
        subtitle_lbl.pack(anchor=tk.W)

        main_frame = tk.Frame(self.root, bg=self.frame_bg, bd=2, relief=tk.RIDGE)
        main_frame.pack(fill=tk.BOTH, expand=True, padx=20, pady=5)

        tk.Label(main_frame, text="Source Pool:", font=("Consolas", 10, "bold"), bg=self.frame_bg, fg=self.accent_color).grid(row=0, column=0, sticky=tk.W, padx=15, pady=15)
        self.src_lbl = tk.Label(main_frame, text=os.path.basename(SOURCE_FILE), font=("Consolas", 9), bg=self.frame_bg)
        self.src_lbl.grid(row=0, column=1, sticky=tk.W, padx=5)

        tk.Label(main_frame, text="Target Vault:", font=("Consolas", 10, "bold"), bg=self.frame_bg, fg=self.accent_color).grid(row=1, column=0, sticky=tk.W, padx=15, pady=5)
        self.out_lbl = tk.Label(main_frame, text=os.path.basename(OUTPUT_FILE), font=("Consolas", 9), bg=self.frame_bg)
        self.out_lbl.grid(row=1, column=1, sticky=tk.W, padx=5)

        tk.Label(main_frame, text="Compile Count:", font=("Consolas", 10, "bold"), bg=self.frame_bg, fg=self.accent_color).grid(row=2, column=0, sticky=tk.W, padx=15, pady=20)
        self.qty_entry = ttk.Entry(main_frame, width=10, font=("Consolas", 10))
        self.qty_entry.insert(0, "10")
        self.qty_entry.grid(row=2, column=1, sticky=tk.W, padx=5)

        self.console_text = tk.Text(main_frame, height=6, width=72, bg="#07010E", fg="#A7F3D0", font=("Consolas", 9), bd=1, relief=tk.SOLID)
        self.console_text.grid(row=3, column=0, columnspan=3, padx=15, pady=10)
        self.console_log("System initialized. Ready to compile.")

        btn_frame = tk.Frame(self.root, bg=self.bg_color)
        btn_frame.pack(fill=tk.X, padx=20, pady=15)

        self.gen_btn = tk.Button(btn_frame, text="► INJECT PROTOCOL", font=("Consolas", 11, "bold"), bg=self.btn_bg, fg="#FFFFFF", bd=0, padx=15, pady=8, command=self.execute_generation)
        self.gen_btn.pack(side=tk.RIGHT)

    def console_log(self, text):
        self.console_text.insert(tk.END, f">> {text}\n")
        self.console_text.see(tk.END)

    def check_source_status(self):
        if os.path.exists(SOURCE_FILE):
            with open(SOURCE_FILE, 'r', encoding='utf-8') as f:
                lines = len(f.readlines()) - 1
            self.console_log(f"Linked data matrix: {lines} active source rows detected.")
        else:
            self.console_log(f"CRITICAL: {SOURCE_FILE} target missing.")

    def execute_generation(self):
        try:
            qty = int(self.qty_entry.get())
            if qty <= 0: raise ValueError
        except ValueError:
            messagebox.showerror("Fault", "Enter a count above 0.")
            return

        try:
            pool = load_source_characters(SOURCE_FILE)
            self.console_log(f"Processing... Merging {qty} new Greek alignment profiles.")
            
            with open(OUTPUT_FILE, mode='w', newline='', encoding='utf-8') as f:
                writer = csv.DictWriter(f, fieldnames=HEADERS)
                writer.writeheader()
                for i in range(1, qty + 1):
                    sampled = random.sample(pool, k=3)
                    card_row = generate_card(i, sampled[0], sampled[1], sampled[2])
                    writer.writerow(card_row)
            
            self.console_log(f"Success. Batch complete! Fused nodes saved to generated_cards.csv.")
            messagebox.showinfo("Secure", f"Successfully generated {qty} new NetP cards!")
        except Exception as e:
            self.console_log(f"FAULT: {str(e)}")

if __name__ == "__main__":
    root = tk.Tk()
    app = R3ALN3T_Console(root)
    root.mainloop()