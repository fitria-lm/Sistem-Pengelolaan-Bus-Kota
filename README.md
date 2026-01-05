# Sistem Pengelolaan Bus Kota - Fitria LM

## 📋 Deskripsi Program
Program **Sistem Pengelolaan Bus Kota** adalah aplikasi berbasis console yang dikembangkan dalam bahasa C++ untuk mengelola operasional transportasi bus kota. Program ini mengintegrasikan berbagai struktur data dan algoritma untuk menyediakan fungsi manajemen halte, bus, jadwal, dan pencarian rute.

## 🏗️ Struktur Data yang Digunakan
1. **Graph** - Untuk merepresentasikan jaringan halte dan rute bus
2. **Binary Search Tree (BST)** - Untuk menyimpan data armada bus
3. **Linked List** - Untuk mengelola jadwal keberangkatan bus

## 🚀 Fitur Utama

### 1. **Dashboard Sistem**
   - Ringkasan statistik sistem
   - Informasi halte dan rute
   - Informasi armada bus
   - Informasi jadwal keberangkatan

### 2. **Pencarian Rute & Jalur**
   - **BFS** - Mencari rute dengan jumlah halte minimum
   - **DFS** - Menampilkan semua kemungkinan rute
   - **Dijkstra** - Mencari rute terpendek berdasarkan jarak
   - Visualisasi peta jaringan halte

### 3. **Manajemen Jadwal**
   - Tampilkan semua jadwal
   - Pencarian jadwal berdasarkan:
     - Nomor plat bus
     - Rute tertentu
     - Waktu keberangkatan

### 4. **Panel Administrator**
   - **Kelola Halte**:
     - Tambah/hapus halte
     - Tambah/hapus rute antar halte
   - **Kelola Bus**:
     - Tambah/hapus bus
     - Edit data bus
     - Ubah status operasional
     - Traversal BST (in-order)
   - **Kelola Jadwal**:
     - Buat/hapus jadwal
     - Edit jadwal
     - Pencarian jadwal

## 🔧 Teknologi dan Algoritma
- **Graph Algorithms**: BFS, DFS, Dijkstra
- **Tree Algorithms**: BST insertion, deletion, traversal
- **Sorting**: Linked list insertion sort untuk jadwal
- **Data Structures**: Graph adjacency list, BST, Linked List

## 📁 Struktur Kode
```
program_busKota_Fitria.cpp
├── Struct dan Class
│   ├── EdgeFitria (Graph edge)
│   ├── NodeBusFitria (BST node)
│   ├── NodeJadwalFitria (Linked list node)
│   ├── GraphFitria (Graph operations)
│   ├── BSTFitria (Binary Search Tree operations)
│   └── LinkedListJadwalFitria (Schedule management)
├── Menu Functions
│   ├── Main menu system
│   ├── Sub-menu for each module
│   └── Helper functions
└── Main Function
    ├── Data initialization (dummy data)
    └── Menu navigation loop
```

## 🛠️ Kompilasi dan Menjalankan Program

### **Kompilasi di Linux/macOS**
```bash
g++ program_busKota_Fitria.cpp -o bus_kota
./bus_kota
```

### **Kompilasi di Windows (MinGW)**
```bash
g++ program_busKota_Fitria.cpp -o bus_kota.exe
bus_kota.exe
```

## 📊 Data Awal (Dummy Data)
Program sudah dilengkapi dengan data awal untuk pengujian:

### **Halte (10 halte)**
- Terminal Kota, Halte Pusat, Halte Utara, Halte Selatan, Halte Timur
- Halte Barat, Halte Stadion, Halte Mall, Halte Stasiun, Halte Bandara

### **Bus (5 armada)**
- B 1234 ABC (Kapasitas: 40, Status: Beroperasi)
- B 5678 DEF (Kapasitas: 35, Status: Beroperasi)
- B 9012 GHI (Kapasitas: 30, Status: Perbaikan)
- B 3456 JKL (Kapasitas: 25, Status: Beroperasi)
- B 7890 MNO (Kapasitas: 20, Status: Cadangan)

### **Jadwal (8 jadwal)**
- Jadwal keberangkatan berbagai bus dengan rute dan waktu berbeda

## 🎯 Cara Menggunakan
1. Jalankan program
2. Pilih menu utama (1-5)
3. Navigasi melalui sub-menu sesuai kebutuhan
4. Gunakan fitur:
   - **Menu 1**: Dashboard untuk melihat ringkasan
   - **Menu 2**: Pencarian rute dengan berbagai algoritma
   - **Menu 3**: Informasi jadwal keberangkatan
   - **Menu 4**: Panel administrator untuk modifikasi data
   - **Menu 5**: Keluar dari program

## ⚙️ Spesifikasi Teknis
- **Bahasa**: C++ (Standard C++11 atau lebih baru)
- **Compiler**: GCC, Clang, atau MSVC
- **Dependencies**: Standard Library saja
- **Sistem Operasi**: Cross-platform (Windows, Linux, macOS)

## 📝 Catatan Pengembangan
- Program menggunakan naming convention dengan suffix "_Fitria" untuk menghindari konflik nama
- Implementasi Graph menggunakan adjacency list dengan std::map
- BST diimplementasikan secara rekursif
- Linked list untuk jadwal diurutkan berdasarkan waktu
- Menu system menggunakan loop bersarang dengan switch-case

## 🤝 Kontribusi
Program ini dikembangkan sebagai proyek akademik. Untuk saran atau perbaikan, silakan hubungi pengembang.

## 📄 Lisensi
Program ini dibuat untuk tujuan edukasi dan dapat digunakan secara bebas dengan mencantumkan sumber.

---
**Dikembangkan oleh:** Fitria LM  
**Mata Kuliah:** Struktur Data
**Institusi:** [Universitas Nusantara PGRI Kediri]