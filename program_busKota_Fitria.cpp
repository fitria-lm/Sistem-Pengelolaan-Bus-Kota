#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
#include <limits>
#include <functional>
using namespace std;

// =================================================
// STRUCT DAN CLASS UTAMA
// =================================================

// Struct untuk edge di graph
struct EdgeFitria {
    string tujuan_Fitria;
    int weight_Fitria;
    EdgeFitria(string t, int w) : tujuan_Fitria(t), weight_Fitria(w) {}
};

// Struct untuk node bus di BST
struct NodeBusFitria {
    string platNomor_Fitria;
    string rute_Fitria;
    int kapasitas_Fitria;
    string status_Fitria;
    NodeBusFitria* left_Fitria;
    NodeBusFitria* right_Fitria;
    
    NodeBusFitria(string plat, string rute, int kap, string status) 
        : platNomor_Fitria(plat), rute_Fitria(rute), kapasitas_Fitria(kap), 
          status_Fitria(status), left_Fitria(nullptr), right_Fitria(nullptr) {}
};

// Struct untuk node jadwal di linked list
struct NodeJadwalFitria {
    string busID_Fitria;
    string rute_Fitria;
    string waktu_Fitria;
    int durasi_Fitria;
    NodeJadwalFitria* next_Fitria;
    
    NodeJadwalFitria(string bus, string rute, string waktu, int durasi)
        : busID_Fitria(bus), rute_Fitria(rute), waktu_Fitria(waktu),
          durasi_Fitria(durasi), next_Fitria(nullptr) {}
};

// =================================================
// CLASS GRAPHFITRIA
// =================================================
class GraphFitria {
private:
    map<string, vector<EdgeFitria>> adjList_Fitria;
    int totalHalte_Fitria;
    
public:
    GraphFitria() : totalHalte_Fitria(0) {}
    
    // Menambahkan halte baru
    void addHalte_Fitria(string nama) {
        if (adjList_Fitria.find(nama) == adjList_Fitria.end()) {
            adjList_Fitria[nama] = vector<EdgeFitria>();
            totalHalte_Fitria++;
            cout << "Halte " << nama << " berhasil ditambahkan.\n";
        } else {
            cout << "Halte " << nama << " sudah ada.\n";
        }
    }
    
    // Menghapus halte
    void deleteHalte_Fitria(string nama) {
        if (adjList_Fitria.erase(nama)) {
            // Hapus semua edge yang menuju ke halte ini
            for (auto& pair : adjList_Fitria) {
                auto& edges = pair.second;
                edges.erase(
                    remove_if(edges.begin(), edges.end(),
                        [nama](const EdgeFitria& e) { return e.tujuan_Fitria == nama; }),
                    edges.end()
                );
            }
            totalHalte_Fitria--;
            cout << "Halte " << nama << " berhasil dihapus.\n";
        } else {
            cout << "Halte " << nama << " tidak ditemukan.\n";
        }
    }
    
    // Menambahkan rute
    void addEdge_Fitria(string from, string to, int weight) {
        if (adjList_Fitria.find(from) == adjList_Fitria.end() || 
            adjList_Fitria.find(to) == adjList_Fitria.end()) {
            cout << "Halte tidak ditemukan.\n";
            return;
        }
        
        // Cek apakah edge sudah ada
        for (const auto& edge : adjList_Fitria[from]) {
            if (edge.tujuan_Fitria == to) {
                cout << "Rute sudah ada.\n";
                return;
            }
        }
        
        adjList_Fitria[from].push_back(EdgeFitria(to, weight));
        adjList_Fitria[to].push_back(EdgeFitria(from, weight)); // undirected graph
        cout << "Rute " << from << " - " << to << " berhasil ditambahkan.\n";
    }
    
    // Menghapus rute
    void deleteEdge_Fitria(string from, string to) {
        if (adjList_Fitria.find(from) == adjList_Fitria.end() || 
            adjList_Fitria.find(to) == adjList_Fitria.end()) {
            cout << "Halte tidak ditemukan.\n";
            return;
        }
        
        // Hapus dari 'from' ke 'to'
        auto& edgesFrom = adjList_Fitria[from];
        edgesFrom.erase(
            remove_if(edgesFrom.begin(), edgesFrom.end(),
                [to](const EdgeFitria& e) { return e.tujuan_Fitria == to; }),
            edgesFrom.end()
        );
        
        // Hapus dari 'to' ke 'from'
        auto& edgesTo = adjList_Fitria[to];
        edgesTo.erase(
            remove_if(edgesTo.begin(), edgesTo.end(),
                [from](const EdgeFitria& e) { return e.tujuan_Fitria == from; }),
            edgesTo.end()
        );
        
        cout << "Rute " << from << " - " << to << " berhasil dihapus.\n";
    }
    
    // Algoritma BFS
    vector<string> BFS_Fitria(string start, string end) {
        vector<string> path_Fitria;
        if (adjList_Fitria.find(start) == adjList_Fitria.end() || 
            adjList_Fitria.find(end) == adjList_Fitria.end()) {
            return path_Fitria;
        }
        
        map<string, bool> visited_Fitria;
        map<string, string> parent_Fitria;
        queue<string> q_Fitria;
        
        q_Fitria.push(start);
        visited_Fitria[start] = true;
        parent_Fitria[start] = "";
        
        while (!q_Fitria.empty()) {
            string current_Fitria = q_Fitria.front();
            q_Fitria.pop();
            
            if (current_Fitria == end) {
                // Rekonstruksi path
                string node_Fitria = end;
                while (node_Fitria != "") {
                    path_Fitria.push_back(node_Fitria);
                    node_Fitria = parent_Fitria[node_Fitria];
                }
                reverse(path_Fitria.begin(), path_Fitria.end());
                return path_Fitria;
            }
            
            for (const auto& edge : adjList_Fitria[current_Fitria]) {
                string neighbor_Fitria = edge.tujuan_Fitria;
                if (!visited_Fitria[neighbor_Fitria]) {
                    visited_Fitria[neighbor_Fitria] = true;
                    parent_Fitria[neighbor_Fitria] = current_Fitria;
                    q_Fitria.push(neighbor_Fitria);
                }
            }
        }
        
        return path_Fitria;
    }
    
    // Algoritma DFS
    vector<vector<string>> DFS_Fitria(string start, string end) {
        vector<vector<string>> allPaths_Fitria;
        if (adjList_Fitria.find(start) == adjList_Fitria.end() || 
            adjList_Fitria.find(end) == adjList_Fitria.end()) {
            return allPaths_Fitria;
        }
        
        map<string, bool> visited_Fitria;
        vector<string> currentPath_Fitria;
        
        function<void(string)> dfsHelper_Fitria = [&](string node_Fitria) {
            visited_Fitria[node_Fitria] = true;
            currentPath_Fitria.push_back(node_Fitria);
            
            if (node_Fitria == end) {
                allPaths_Fitria.push_back(currentPath_Fitria);
            } else {
                for (const auto& edge : adjList_Fitria[node_Fitria]) {
                    string neighbor_Fitria = edge.tujuan_Fitria;
                    if (!visited_Fitria[neighbor_Fitria]) {
                        dfsHelper_Fitria(neighbor_Fitria);
                    }
                }
            }
            
            visited_Fitria[node_Fitria] = false;
            currentPath_Fitria.pop_back();
        };
        
        dfsHelper_Fitria(start);
        return allPaths_Fitria;
    }
    
    // Algoritma Dijkstra
    pair<vector<string>, int> dijkstra_Fitria(string start, string end) {
        vector<string> path_Fitria;
        int totalDistance_Fitria = -1;
        
        if (adjList_Fitria.find(start) == adjList_Fitria.end() || 
            adjList_Fitria.find(end) == adjList_Fitria.end()) {
            return {path_Fitria, totalDistance_Fitria};
        }
        
        map<string, int> dist_Fitria;
        map<string, string> parent_Fitria;
        map<string, bool> processed_Fitria;
        
        for (const auto& pair : adjList_Fitria) {
            dist_Fitria[pair.first] = numeric_limits<int>::max();
        }
        
        dist_Fitria[start] = 0;
        parent_Fitria[start] = "";
        
        // Priority queue sederhana
        for (int i = 0; i < totalHalte_Fitria; i++) {
            string minNode_Fitria = "";
            int minDist_Fitria = numeric_limits<int>::max();
            
            for (const auto& pair : dist_Fitria) {
                if (!processed_Fitria[pair.first] && pair.second < minDist_Fitria) {
                    minDist_Fitria = pair.second;
                    minNode_Fitria = pair.first;
                }
            }
            
            if (minNode_Fitria == "") break;
            processed_Fitria[minNode_Fitria] = true;
            
            if (minNode_Fitria == end) break;
            
            for (const auto& edge : adjList_Fitria[minNode_Fitria]) {
                string neighbor_Fitria = edge.tujuan_Fitria;
                int weight_Fitria = edge.weight_Fitria;
                
                if (dist_Fitria[minNode_Fitria] + weight_Fitria < dist_Fitria[neighbor_Fitria]) {
                    dist_Fitria[neighbor_Fitria] = dist_Fitria[minNode_Fitria] + weight_Fitria;
                    parent_Fitria[neighbor_Fitria] = minNode_Fitria;
                }
            }
        }
        
        if (dist_Fitria[end] != numeric_limits<int>::max()) {
            // Rekonstruksi path
            string node_Fitria = end;
            while (node_Fitria != "") {
                path_Fitria.push_back(node_Fitria);
                node_Fitria = parent_Fitria[node_Fitria];
            }
            reverse(path_Fitria.begin(), path_Fitria.end());
            totalDistance_Fitria = dist_Fitria[end];
        }
        
        return {path_Fitria, totalDistance_Fitria};
    }
    
    // Menampilkan semua halte
    void displayAllHalte_Fitria() {
        cout << "\nDaftar Halte (" << totalHalte_Fitria << " halte):\n";
        cout << "-----------------------------------------\n";
        int count_Fitria = 1;
        for (const auto& pair : adjList_Fitria) {
            cout << count_Fitria << ". " << pair.first << " (Tujuan: " << pair.second.size() << " rute)\n";
            count_Fitria++;
        }
    }
    
    // Menampilkan adjacency list
    void displayAdjList_Fitria() {
        cout << "\nPeta Jaringan Halte:\n";
        cout << "-----------------------------------------\n";
        for (const auto& pair : adjList_Fitria) {
            cout << "Halte " << pair.first << " terhubung ke:\n";
            for (const auto& edge : pair.second) {
                cout << "  -> " << edge.tujuan_Fitria << " (" << edge.weight_Fitria << " km)\n";
            }
            cout << endl;
        }
    }
    
    // Getter
    int getTotalHalte_Fitria() { return totalHalte_Fitria; }
    bool halteExists_Fitria(string nama) { 
        return adjList_Fitria.find(nama) != adjList_Fitria.end(); 
    }
};

// =================================================
// CLASS BSTFITRIA
// =================================================
class BSTFitria {
private:
    NodeBusFitria* root_Fitria;
    int totalBus_Fitria;
    
    // Helper untuk insert
    NodeBusFitria* insertRec_Fitria(NodeBusFitria* node, NodeBusFitria* newNode) {
        if (node == nullptr) return newNode;
        
        if (newNode->platNomor_Fitria < node->platNomor_Fitria) {
            node->left_Fitria = insertRec_Fitria(node->left_Fitria, newNode);
        } else if (newNode->platNomor_Fitria > node->platNomor_Fitria) {
            node->right_Fitria = insertRec_Fitria(node->right_Fitria, newNode);
        }
        
        return node;
    }
    
    // Helper untuk inorder traversal
    void inorderRec_Fitria(NodeBusFitria* node) {
        if (node == nullptr) return;
        
        inorderRec_Fitria(node->left_Fitria);
        cout << "  - " << node->platNomor_Fitria << " | Rute: " << node->rute_Fitria 
             << " | Kapasitas: " << node->kapasitas_Fitria 
             << " | Status: " << node->status_Fitria << endl;
        inorderRec_Fitria(node->right_Fitria);
    }
    
    // Helper untuk search
    NodeBusFitria* searchRec_Fitria(NodeBusFitria* node, string platNomor) {
        if (node == nullptr || node->platNomor_Fitria == platNomor) {
            return node;
        }
        
        if (platNomor < node->platNomor_Fitria) {
            return searchRec_Fitria(node->left_Fitria, platNomor);
        } else {
            return searchRec_Fitria(node->right_Fitria, platNomor);
        }
    }
    
    // Helper untuk find minimum
    NodeBusFitria* findMin_Fitria(NodeBusFitria* node) {
        while (node && node->left_Fitria != nullptr) {
            node = node->left_Fitria;
        }
        return node;
    }
    
    // Helper untuk delete
    NodeBusFitria* deleteRec_Fitria(NodeBusFitria* node, string platNomor) {
        if (node == nullptr) return nullptr;
        
        if (platNomor < node->platNomor_Fitria) {
            node->left_Fitria = deleteRec_Fitria(node->left_Fitria, platNomor);
        } else if (platNomor > node->platNomor_Fitria) {
            node->right_Fitria = deleteRec_Fitria(node->right_Fitria, platNomor);
        } else {
            // Node ditemukan
            totalBus_Fitria--;
            
            // Case 1: No child
            if (node->left_Fitria == nullptr && node->right_Fitria == nullptr) {
                delete node;
                return nullptr;
            }
            // Case 2: One child
            else if (node->left_Fitria == nullptr) {
                NodeBusFitria* temp_Fitria = node->right_Fitria;
                delete node;
                return temp_Fitria;
            } else if (node->right_Fitria == nullptr) {
                NodeBusFitria* temp_Fitria = node->left_Fitria;
                delete node;
                return temp_Fitria;
            }
            // Case 3: Two children
            else {
                NodeBusFitria* temp_Fitria = findMin_Fitria(node->right_Fitria);
                node->platNomor_Fitria = temp_Fitria->platNomor_Fitria;
                node->rute_Fitria = temp_Fitria->rute_Fitria;
                node->kapasitas_Fitria = temp_Fitria->kapasitas_Fitria;
                node->status_Fitria = temp_Fitria->status_Fitria;
                node->right_Fitria = deleteRec_Fitria(node->right_Fitria, temp_Fitria->platNomor_Fitria);
            }
        }
        
        return node;
    }
    
public:
    BSTFitria() : root_Fitria(nullptr), totalBus_Fitria(0) {}
    
    // Insert bus baru
    void insertBus_Fitria(string plat, string rute, int kapasitas, string status) {
        NodeBusFitria* newNode_Fitria = new NodeBusFitria(plat, rute, kapasitas, status);
        
        if (searchRec_Fitria(root_Fitria, plat) != nullptr) {
            cout << "Bus dengan plat " << plat << " sudah ada.\n";
            delete newNode_Fitria;
            return;
        }
        
        root_Fitria = insertRec_Fitria(root_Fitria, newNode_Fitria);
        totalBus_Fitria++;
        cout << "Bus " << plat << " berhasil ditambahkan.\n";
    }
    
    // Delete bus
    void deleteBus_Fitria(string platNomor) {
        NodeBusFitria* found_Fitria = searchRec_Fitria(root_Fitria, platNomor);
        if (found_Fitria == nullptr) {
            cout << "Bus dengan plat " << platNomor << " tidak ditemukan.\n";
            return;
        }
        
        root_Fitria = deleteRec_Fitria(root_Fitria, platNomor);
        cout << "Bus " << platNomor << " berhasil dihapus.\n";
    }
    
    // Search bus
    NodeBusFitria* searchBus_Fitria(string platNomor) {
        return searchRec_Fitria(root_Fitria, platNomor);
    }
    
    // Update bus
    void updateBus_Fitria(string platNomor, string newRute, int newKapasitas, string newStatus) {
        NodeBusFitria* bus_Fitria = searchRec_Fitria(root_Fitria, platNomor);
        if (bus_Fitria == nullptr) {
            cout << "Bus tidak ditemukan.\n";
            return;
        }
        
        bus_Fitria->rute_Fitria = newRute;
        bus_Fitria->kapasitas_Fitria = newKapasitas;
        bus_Fitria->status_Fitria = newStatus;
        cout << "Data bus " << platNomor << " berhasil diupdate.\n";
    }
    
    // In-order traversal
    void displayInOrder_Fitria() {
        cout << "\nDaftar Bus (In-Order Traversal):\n";
        cout << "-----------------------------------------\n";
        if (root_Fitria == nullptr) {
            cout << "Tidak ada bus.\n";
            return;
        }
        inorderRec_Fitria(root_Fitria);
    }
    
    // Display semua bus
    void displayAllBus_Fitria() {
        cout << "\nDaftar Semua Bus (" << totalBus_Fitria << " bus):\n";
        cout << "-----------------------------------------\n";
        if (root_Fitria == nullptr) {
            cout << "Tidak ada bus.\n";
            return;
        }
        
        // Menggunakan queue untuk level order (BFS-like)
        queue<NodeBusFitria*> q_Fitria;
        q_Fitria.push(root_Fitria);
        int count_Fitria = 1;
        
        while (!q_Fitria.empty()) {
            int levelSize_Fitria = q_Fitria.size();
            
            for (int i = 0; i < levelSize_Fitria; i++) {
                NodeBusFitria* current_Fitria = q_Fitria.front();
                q_Fitria.pop();
                
                cout << count_Fitria << ". Plat: " << current_Fitria->platNomor_Fitria
                     << " | Rute: " << current_Fitria->rute_Fitria
                     << " | Kapasitas: " << current_Fitria->kapasitas_Fitria
                     << " | Status: " << current_Fitria->status_Fitria << endl;
                count_Fitria++;
                
                if (current_Fitria->left_Fitria != nullptr) {
                    q_Fitria.push(current_Fitria->left_Fitria);
                }
                if (current_Fitria->right_Fitria != nullptr) {
                    q_Fitria.push(current_Fitria->right_Fitria);
                }
            }
        }
    }
    
    // Getter
    int getTotalBus_Fitria() { return totalBus_Fitria; }
    
    // Statistik status
    void displayBusStats_Fitria() {
        map<string, int> stats_Fitria;
        function<void(NodeBusFitria*)> countStats_Fitria = [&](NodeBusFitria* node) {
            if (node == nullptr) return;
            stats_Fitria[node->status_Fitria]++;
            countStats_Fitria(node->left_Fitria);
            countStats_Fitria(node->right_Fitria);
        };
        
        countStats_Fitria(root_Fitria);
        
        cout << "\nStatistik Armada Bus:\n";
        cout << "-----------------------------------------\n";
        cout << "Total Bus: " << totalBus_Fitria << endl;
        for (const auto& stat : stats_Fitria) {
            cout << "Status " << stat.first << ": " << stat.second << " bus\n";
        }
    }
};

// =================================================
// CLASS LINKEDLISTJADWALFITRIA
// =================================================
class LinkedListJadwalFitria {
private:
    NodeJadwalFitria* head_Fitria;
    int totalJadwal_Fitria;
    
public:
    LinkedListJadwalFitria() : head_Fitria(nullptr), totalJadwal_Fitria(0) {}
    
    // Insert jadwal (sorted by waktu)
    void insertJadwal_Fitria(string busID, string rute, string waktu, int durasi) {
        NodeJadwalFitria* newNode_Fitria = new NodeJadwalFitria(busID, rute, waktu, durasi);
        
        if (head_Fitria == nullptr || waktu < head_Fitria->waktu_Fitria) {
            newNode_Fitria->next_Fitria = head_Fitria;
            head_Fitria = newNode_Fitria;
        } else {
            NodeJadwalFitria* current_Fitria = head_Fitria;
            while (current_Fitria->next_Fitria != nullptr && 
                   current_Fitria->next_Fitria->waktu_Fitria < waktu) {
                current_Fitria = current_Fitria->next_Fitria;
            }
            newNode_Fitria->next_Fitria = current_Fitria->next_Fitria;
            current_Fitria->next_Fitria = newNode_Fitria;
        }
        
        totalJadwal_Fitria++;
        cout << "Jadwal berhasil ditambahkan.\n";
    }
    
    // Delete jadwal
    void deleteJadwal_Fitria(string busID, string waktu) {
        if (head_Fitria == nullptr) {
            cout << "Tidak ada jadwal.\n";
            return;
        }
        
        // Jika head yang akan dihapus
        if (head_Fitria->busID_Fitria == busID && head_Fitria->waktu_Fitria == waktu) {
            NodeJadwalFitria* temp_Fitria = head_Fitria;
            head_Fitria = head_Fitria->next_Fitria;
            delete temp_Fitria;
            totalJadwal_Fitria--;
            cout << "Jadwal berhasil dihapus.\n";
            return;
        }
        
        // Cari node sebelumnya
        NodeJadwalFitria* current_Fitria = head_Fitria;
        while (current_Fitria->next_Fitria != nullptr && 
               !(current_Fitria->next_Fitria->busID_Fitria == busID && 
                 current_Fitria->next_Fitria->waktu_Fitria == waktu)) {
            current_Fitria = current_Fitria->next_Fitria;
        }
        
        if (current_Fitria->next_Fitria != nullptr) {
            NodeJadwalFitria* temp_Fitria = current_Fitria->next_Fitria;
            current_Fitria->next_Fitria = temp_Fitria->next_Fitria;
            delete temp_Fitria;
            totalJadwal_Fitria--;
            cout << "Jadwal berhasil dihapus.\n";
        } else {
            cout << "Jadwal tidak ditemukan.\n";
        }
    }
    
    // Search jadwal by bus
    vector<NodeJadwalFitria*> searchByBus_Fitria(string busID) {
        vector<NodeJadwalFitria*> result_Fitria;
        NodeJadwalFitria* current_Fitria = head_Fitria;
        
        while (current_Fitria != nullptr) {
            if (current_Fitria->busID_Fitria == busID) {
                result_Fitria.push_back(current_Fitria);
            }
            current_Fitria = current_Fitria->next_Fitria;
        }
        
        return result_Fitria;
    }
    
    // Search jadwal by rute
    vector<NodeJadwalFitria*> searchByRute_Fitria(string rute) {
        vector<NodeJadwalFitria*> result_Fitria;
        NodeJadwalFitria* current_Fitria = head_Fitria;
        
        while (current_Fitria != nullptr) {
            if (current_Fitria->rute_Fitria == rute) {
                result_Fitria.push_back(current_Fitria);
            }
            current_Fitria = current_Fitria->next_Fitria;
        }
        
        return result_Fitria;
    }
    
    // Search jadwal by waktu
    vector<NodeJadwalFitria*> searchByWaktu_Fitria(string waktu) {
        vector<NodeJadwalFitria*> result_Fitria;
        NodeJadwalFitria* current_Fitria = head_Fitria;
        
        while (current_Fitria != nullptr) {
            if (current_Fitria->waktu_Fitria == waktu) {
                result_Fitria.push_back(current_Fitria);
            }
            current_Fitria = current_Fitria->next_Fitria;
        }
        
        return result_Fitria;
    }
    
    // Display semua jadwal
    void displayAllJadwal_Fitria() {
        cout << "\nDaftar Semua Jadwal (" << totalJadwal_Fitria << " jadwal):\n";
        cout << "-----------------------------------------\n";
        
        if (head_Fitria == nullptr) {
            cout << "Tidak ada jadwal.\n";
            return;
        }
        
        NodeJadwalFitria* current_Fitria = head_Fitria;
        int count_Fitria = 1;
        
        while (current_Fitria != nullptr) {
            cout << count_Fitria << ". Bus: " << current_Fitria->busID_Fitria
                 << " | Rute: " << current_Fitria->rute_Fitria
                 << " | Waktu: " << current_Fitria->waktu_Fitria
                 << " | Durasi: " << current_Fitria->durasi_Fitria << " menit\n";
            current_Fitria = current_Fitria->next_Fitria;
            count_Fitria++;
        }
    }
    
    // Getter
    int getTotalJadwal_Fitria() { return totalJadwal_Fitria; }
};

// =================================================
// FUNGSI DISPLAY MENU
// =================================================

void displayMainMenu_Fitria() {
    cout << "\n=================================================\n";
    cout << "     SISTEM PENGELOLAAN BUS KOTA - FITRIA LM\n";
    cout << "=================================================\n";
    cout << "Menu 1: Dashboard Sistem\n";
    cout << "Menu 2: Pencarian Rute & Jalur\n";
    cout << "Menu 3: Informasi Jadwal\n";
    cout << "Menu 4: Panel Administrator\n";
    cout << "Menu 5: Keluar\n";
    cout << "=================================================\n";
    cout << "Pilih menu (1/2/3/4/5): ";
}

void displayDashboardMenu_Fitria() {
    cout << "\n-------------------------------------------------\n";
    cout << "          DASHBOARD SISTEM\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Ringkasan Sistem\n";
    cout << "2. Info Halte & Rute\n";
    cout << "3. Info Armada Bus\n";
    cout << "4. Info Jadwal Keberangkatan\n";
    cout << "5. Kembali ke Menu Utama\n";
    cout << "-------------------------------------------------\n";
    cout << "Pilihan Anda: ";
}

void displayPencarianMenu_Fitria() {
    cout << "\n-------------------------------------------------\n";
    cout << "          PENCARIAN RUTE & JALUR\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Cari Rute (BFS - minimum halte)\n";
    cout << "2. Cari Rute (DFS - semua kemungkinan)\n";
    cout << "3. Cari Rute Terpendek (Dijkstra)\n";
    cout << "4. Lihat Peta Jaringan\n";
    cout << "5. Kembali ke Menu Utama\n";
    cout << "-------------------------------------------------\n";
    cout << "Pilihan Anda: ";
}

void displayJadwalMenu_Fitria() {
    cout << "\n-------------------------------------------------\n";
    cout << "          INFORMASI JADWAL\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Tampilkan Semua Jadwal\n";
    cout << "2. Cari Jadwal Berdasarkan Bus\n";
    cout << "3. Cari Jadwal Berdasarkan Rute\n";
    cout << "4. Cari Jadwal Berdasarkan Waktu\n";
    cout << "5. Kembali ke Menu Utama\n";
    cout << "-------------------------------------------------\n";
    cout << "Pilihan Anda: ";
}

void displayAdminMenu_Fitria() {
    cout << "\n-------------------------------------------------\n";
    cout << "          PANEL ADMINISTRATOR\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Kelola Data Halte\n";
    cout << "2. Kelola Data Bus\n";
    cout << "3. Kelola Jadwal\n";
    cout << "4. Kembali ke Menu Utama\n";
    cout << "-------------------------------------------------\n";
    cout << "Pilihan Anda: ";
}

void displayHalteMenu_Fitria() {
    cout << "\n-------------------------------------------------\n";
    cout << "          KELOLA DATA HALTE\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Tambah Halte Baru\n";
    cout << "2. Hapus Halte\n";
    cout << "3. Tambah Rute Baru\n";
    cout << "4. Hapus Rute\n";
    cout << "5. Tampilkan Semua Halte\n";
    cout << "6. Kembali ke Menu Administrator\n";
    cout << "-------------------------------------------------\n";
    cout << "Pilihan Anda: ";
}

void displayBusMenu_Fitria() {
    cout << "\n-------------------------------------------------\n";
    cout << "          KELOLA DATA BUS\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Tambah Bus Baru\n";
    cout << "2. Hapus Bus\n";
    cout << "3. Cari + Edit Bus\n";
    cout << "4. Ubah Status Bus\n";
    cout << "5. Tampilkan Semua Bus\n";
    cout << "6. In-Order Traversal\n";
    cout << "7. Kembali ke Menu Administrator\n";
    cout << "-------------------------------------------------\n";
    cout << "Pilihan Anda: ";
}

void displayJadwalAdminMenu_Fitria() {
    cout << "\n-------------------------------------------------\n";
    cout << "          KELOLA JADWAL\n";
    cout << "-------------------------------------------------\n";
    cout << "1. Cari Jadwal\n";
    cout << "2. Buat Jadwal Baru\n";
    cout << "3. Hapus Jadwal\n";
    cout << "4. Edit Jadwal\n";
    cout << "5. Tampilkan Semua Jadwal\n";
    cout << "6. Kembali ke Menu Administrator\n";
    cout << "-------------------------------------------------\n";
    cout << "Pilihan Anda: ";
}

// =================================================
// FUNGSI HELPER
// =================================================

void clearScreen_Fitria() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pause_Fitria() {
    cout << "\nTekan Enter untuk melanjutkan...";
    cin.ignore();
    cin.get();
}

// =================================================
// FUNGSI UTAMA
// =================================================

int main() {
    // Inisialisasi data
    GraphFitria graph;
    BSTFitria bst;
    LinkedListJadwalFitria jadwal;
    
    // Data dummy halte
    vector<string> halteDummy_Fitria = {"Terminal Kota", "Halte Pusat", "Halte Utara", 
                                       "Halte Selatan", "Halte Timur", "Halte Barat",
                                       "Halte Stadion", "Halte Mall", "Halte Stasiun", 
                                       "Halte Bandara"};
    
    for (const auto& halte : halteDummy_Fitria) {
        graph.addHalte_Fitria(halte);
    }
    
    // Data dummy rute (undirected graph)
    graph.addEdge_Fitria("Terminal Kota", "Halte Pusat", 5);
    graph.addEdge_Fitria("Halte Pusat", "Halte Utara", 3);
    graph.addEdge_Fitria("Halte Pusat", "Halte Selatan", 4);
    graph.addEdge_Fitria("Halte Utara", "Halte Timur", 6);
    graph.addEdge_Fitria("Halte Selatan", "Halte Barat", 5);
    graph.addEdge_Fitria("Halte Timur", "Halte Stadion", 2);
    graph.addEdge_Fitria("Halte Barat", "Halte Mall", 3);
    graph.addEdge_Fitria("Halte Mall", "Halte Stasiun", 4);
    graph.addEdge_Fitria("Halte Stasiun", "Halte Bandara", 10);
    graph.addEdge_Fitria("Terminal Kota", "Halte Bandara", 15);
    
    // Data dummy bus
    bst.insertBus_Fitria("B 1234 ABC", "Kota - Bandara", 40, "Beroperasi");
    bst.insertBus_Fitria("B 5678 DEF", "Utara - Selatan", 35, "Beroperasi");
    bst.insertBus_Fitria("B 9012 GHI", "Timur - Barat", 30, "Perbaikan");
    bst.insertBus_Fitria("B 3456 JKL", "Pusat - Stadion", 25, "Beroperasi");
    bst.insertBus_Fitria("B 7890 MNO", "Mall - Stasiun", 20, "Cadangan");
    
    // Data dummy jadwal
    jadwal.insertJadwal_Fitria("B 1234 ABC", "Kota - Bandara", "08:00", 45);
    jadwal.insertJadwal_Fitria("B 5678 DEF", "Utara - Selatan", "09:30", 30);
    jadwal.insertJadwal_Fitria("B 1234 ABC", "Kota - Bandara", "14:00", 45);
    jadwal.insertJadwal_Fitria("B 3456 JKL", "Pusat - Stadion", "10:15", 20);
    jadwal.insertJadwal_Fitria("B 5678 DEF", "Utara - Selatan", "16:45", 30);
    jadwal.insertJadwal_Fitria("B 1234 ABC", "Kota - Bandara", "18:30", 45);
    jadwal.insertJadwal_Fitria("B 3456 JKL", "Pusat - Stadion", "13:20", 20);
    jadwal.insertJadwal_Fitria("B 5678 DEF", "Utara - Selatan", "20:00", 30);
    
    int mainChoice_Fitria;
    bool running_Fitria = true;
    
    while (running_Fitria) {
        clearScreen_Fitria();
        displayMainMenu_Fitria();
        cin >> mainChoice_Fitria;
        
        switch (mainChoice_Fitria) {
            case 1: { // Dashboard Sistem
                int dashboardChoice_Fitria;
                do {
                    clearScreen_Fitria();
                    displayDashboardMenu_Fitria();
                    cin >> dashboardChoice_Fitria;
                    
                    switch (dashboardChoice_Fitria) {
                        case 1: { // Ringkasan Sistem
                            clearScreen_Fitria();
                            cout << "\n-----------------------------------------\n";
                            cout << "          RINGKASAN SISTEM\n";
                            cout << "-----------------------------------------\n";
                            cout << "Statistik Sistem:\n\n";
                            cout << "Total Halte: " << graph.getTotalHalte_Fitria() << endl;
                            cout << "Total Bus: " << bst.getTotalBus_Fitria() << endl;
                            cout << "Total Jadwal: " << jadwal.getTotalJadwal_Fitria() << endl;
                            cout << "\nStatus Sistem: NORMAL\n";
                            cout << "Update Terakhir: " << __TIME__ << endl;
                            cout << "-----------------------------------------\n";
                            pause_Fitria();
                            break;
                        }
                        case 2: { // Info Halte & Rute
                            graph.displayAllHalte_Fitria();
                            pause_Fitria();
                            break;
                        }
                        case 3: { // Info Armada Bus
                            bst.displayBusStats_Fitria();
                            bst.displayAllBus_Fitria();
                            pause_Fitria();
                            break;
                        }
                        case 4: { // Info Jadwal
                            jadwal.displayAllJadwal_Fitria();
                            pause_Fitria();
                            break;
                        }
                    }
                } while (dashboardChoice_Fitria != 5);
                break;
            }
            
            case 2: { // Pencarian Rute & Jalur
                int pencarianChoice_Fitria;
                do {
                    clearScreen_Fitria();
                    displayPencarianMenu_Fitria();
                    cin >> pencarianChoice_Fitria;
                    
                    switch (pencarianChoice_Fitria) {
                        case 1: { // BFS
                            string start_Fitria, end_Fitria;
                            cout << "Masukkan halte awal: ";
                            cin.ignore();
                            getline(cin, start_Fitria);
                            cout << "Masukkan halte tujuan: ";
                            getline(cin, end_Fitria);
                            
                            vector<string> path_Fitria = graph.BFS_Fitria(start_Fitria, end_Fitria);
                            
                            if (path_Fitria.empty()) {
                                cout << "Rute tidak ditemukan.\n";
                            } else {
                                cout << "\nRute (BFS - minimum halte):\n";
                                cout << "-----------------------------------------\n";
                                for (size_t i = 0; i < path_Fitria.size(); i++) {
                                    cout << path_Fitria[i];
                                    if (i < path_Fitria.size() - 1) {
                                        cout << " -> ";
                                    }
                                }
                                cout << "\nTotal halte: " << path_Fitria.size() << endl;
                            }
                            pause_Fitria();
                            break;
                        }
                        case 2: { // DFS
                            string start_Fitria, end_Fitria;
                            cout << "Masukkan halte awal: ";
                            cin.ignore();
                            getline(cin, start_Fitria);
                            cout << "Masukkan halte tujuan: ";
                            getline(cin, end_Fitria);
                            
                            vector<vector<string>> allPaths_Fitria = graph.DFS_Fitria(start_Fitria, end_Fitria);
                            
                            if (allPaths_Fitria.empty()) {
                                cout << "Rute tidak ditemukan.\n";
                            } else {
                                cout << "\nSemua Rute (DFS):\n";
                                cout << "-----------------------------------------\n";
                                for (size_t i = 0; i < allPaths_Fitria.size(); i++) {
                                    cout << "Rute " << i+1 << ": ";
                                    for (size_t j = 0; j < allPaths_Fitria[i].size(); j++) {
                                        cout << allPaths_Fitria[i][j];
                                        if (j < allPaths_Fitria[i].size() - 1) {
                                            cout << " -> ";
                                        }
                                    }
                                    cout << " (" << allPaths_Fitria[i].size() << " halte)\n";
                                }
                            }
                            pause_Fitria();
                            break;
                        }
                        case 3: { // Dijkstra
                            string start_Fitria, end_Fitria;
                            cout << "Masukkan halte awal: ";
                            cin.ignore();
                            getline(cin, start_Fitria);
                            cout << "Masukkan halte tujuan: ";
                            getline(cin, end_Fitria);
                            
                            auto result_Fitria = graph.dijkstra_Fitria(start_Fitria, end_Fitria);
                            vector<string> path_Fitria = result_Fitria.first;
                            int distance_Fitria = result_Fitria.second;
                            
                            if (path_Fitria.empty()) {
                                cout << "Rute tidak ditemukan.\n";
                            } else {
                                cout << "\nRute Terpendek (Dijkstra):\n";
                                cout << "-----------------------------------------\n";
                                for (size_t i = 0; i < path_Fitria.size(); i++) {
                                    cout << path_Fitria[i];
                                    if (i < path_Fitria.size() - 1) {
                                        cout << " -> ";
                                    }
                                }
                                cout << "\nTotal jarak: " << distance_Fitria << " km\n";
                            }
                            pause_Fitria();
                            break;
                        }
                        case 4: { // Peta Jaringan
                            clearScreen_Fitria();
                            graph.displayAdjList_Fitria();
                            pause_Fitria();
                            break;
                        }
                    }
                } while (pencarianChoice_Fitria != 5);
                break;
            }
            
            case 3: { // Informasi Jadwal
                int jadwalChoice_Fitria;
                do {
                    clearScreen_Fitria();
                    displayJadwalMenu_Fitria();
                    cin >> jadwalChoice_Fitria;
                    
                    switch (jadwalChoice_Fitria) {
                        case 1: { // Tampilkan semua
                            jadwal.displayAllJadwal_Fitria();
                            pause_Fitria();
                            break;
                        }
                        case 2: { // Cari by bus
                            string busID_Fitria;
                            cout << "Masukkan plat nomor bus: ";
                            cin.ignore();
                            getline(cin, busID_Fitria);

                            vector<NodeJadwalFitria*> results_Fitria = jadwal.searchByBus_Fitria(busID_Fitria);
                            
                            if (results_Fitria.empty()) {
                                cout << "Tidak ditemukan jadwal untuk bus " << busID_Fitria << endl;
                            } else {
                                cout << "\nJadwal untuk bus " << busID_Fitria << ":\n";
                                cout << "-----------------------------------------\n";
                                for (size_t i = 0; i < results_Fitria.size(); i++) {
                                    cout << i+1 << ". Rute: " << results_Fitria[i]->rute_Fitria
                                         << " | Waktu: " << results_Fitria[i]->waktu_Fitria
                                         << " | Durasi: " << results_Fitria[i]->durasi_Fitria << " menit\n";
                                }
                            }
                            pause_Fitria();
                            break;
                        }
                        case 3: { // Cari by rute
                            string rute_Fitria;
                            cout << "Masukkan rute: ";
                            cin.ignore();
                            getline(cin, rute_Fitria);
                            
                            vector<NodeJadwalFitria*> results_Fitria = jadwal.searchByRute_Fitria(rute_Fitria);
                            
                            if (results_Fitria.empty()) {
                                cout << "Tidak ditemukan jadwal untuk rute " << rute_Fitria << endl;
                            } else {
                                cout << "\nJadwal untuk rute " << rute_Fitria << ":\n";
                                cout << "-----------------------------------------\n";
                                for (size_t i = 0; i < results_Fitria.size(); i++) {
                                    cout << i+1 << ". Bus: " << results_Fitria[i]->busID_Fitria
                                         << " | Waktu: " << results_Fitria[i]->waktu_Fitria
                                         << " | Durasi: " << results_Fitria[i]->durasi_Fitria << " menit\n";
                                }
                            }
                            pause_Fitria();
                            break;
                        }
                        case 4: { // Cari by waktu
                            string waktu_Fitria;
                            cout << "Masukkan waktu (HH:MM): ";
                            cin >> waktu_Fitria;
                            
                            vector<NodeJadwalFitria*> results_Fitria = jadwal.searchByWaktu_Fitria(waktu_Fitria);
                            
                            if (results_Fitria.empty()) {
                                cout << "Tidak ditemukan jadwal pada waktu " << waktu_Fitria << endl;
                            } else {
                                cout << "\nJadwal pada waktu " << waktu_Fitria << ":\n";
                                cout << "-----------------------------------------\n";
                                for (size_t i = 0; i < results_Fitria.size(); i++) {
                                    cout << i+1 << ". Bus: " << results_Fitria[i]->busID_Fitria
                                         << " | Rute: " << results_Fitria[i]->rute_Fitria
                                         << " | Durasi: " << results_Fitria[i]->durasi_Fitria << " menit\n";
                                }
                            }
                            pause_Fitria();
                            break;
                        }
                    }
                } while (jadwalChoice_Fitria != 5);
                break;
            }
            
            case 4: { // Panel Administrator
                int adminChoice_Fitria;
                do {
                    clearScreen_Fitria();
                    displayAdminMenu_Fitria();
                    cin >> adminChoice_Fitria;
                    
                    switch (adminChoice_Fitria) {
                        case 1: { // Kelola Halte
                            int halteChoice_Fitria;
                            do {
                                clearScreen_Fitria();
                                displayHalteMenu_Fitria();
                                cin >> halteChoice_Fitria;
                                
                                switch (halteChoice_Fitria) {
                                    case 1: { // Tambah halte
                                        string nama_Fitria;
                                        cout << "Masukkan nama halte: ";
                                        cin.ignore();
                                        getline(cin, nama_Fitria);
                                        graph.addHalte_Fitria(nama_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 2: { // Hapus halte
                                        string nama_Fitria;
                                        cout << "Masukkan nama halte: ";
                                        cin.ignore();
                                        getline(cin, nama_Fitria);
                                        graph.deleteHalte_Fitria(nama_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 3: { // Tambah rute
                                        string from_Fitria, to_Fitria;
                                        int weight_Fitria;
                                        cout << "Masukkan halte awal: ";
                                        cin.ignore();
                                        getline(cin, from_Fitria);                                        
                                        cout << "Masukkan halte tujuan: ";
                                        cin.ignore();
                                        getline(cin, to_Fitria);
                                        cout << "Masukkan jarak (km): ";
                                        cin >> weight_Fitria;
                                        graph.addEdge_Fitria(from_Fitria, to_Fitria, weight_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 4: { // Hapus rute
                                        string from_Fitria, to_Fitria;
                                        cout << "Masukkan halte awal: ";
                                        cin.ignore();
                                        getline(cin, from_Fitria);
                                        cout << "Masukkan halte tujuan: ";
                                        cin.ignore();
                                        getline(cin, to_Fitria);
                                        graph.deleteEdge_Fitria(from_Fitria, to_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 5: { // Tampilkan semua
                                        graph.displayAllHalte_Fitria();
                                        pause_Fitria();
                                        break;
                                    }
                                }
                            } while (halteChoice_Fitria != 6);
                            break;
                        }
                        
                        case 2: { // Kelola Bus
                            int busChoice_Fitria;
                            do {
                                clearScreen_Fitria();
                                displayBusMenu_Fitria();
                                cin >> busChoice_Fitria;
                                
                                switch (busChoice_Fitria) {
                                    case 1: { // Tambah bus
                                        string plat_Fitria, rute_Fitria, status_Fitria;
                                        int kapasitas_Fitria;
                                        cout << "Masukkan plat nomor: ";
                                        cin.ignore();
                                        getline(cin, plat_Fitria);
                                        cout << "Masukkan rute: ";
                                        cin.ignore();
                                        getline(cin, rute_Fitria);
                                        cout << "Masukkan kapasitas: ";
                                        cin >> kapasitas_Fitria;
                                        cout << "Masukkan status (Beroperasi/Perbaikan/Cadangan): ";
                                        cin.ignore();
                                        getline(cin, status_Fitria);
                                        bst.insertBus_Fitria(plat_Fitria, rute_Fitria, kapasitas_Fitria, status_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 2: { // Hapus bus
                                        string plat_Fitria;
                                        cout << "Masukkan plat nomor: ";
                                        cin.ignore();
                                        getline(cin, plat_Fitria);
                                        bst.deleteBus_Fitria(plat_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 3: { // Cari & edit bus
                                        string plat_Fitria;
                                        cout << "Masukkan plat nomor: ";
                                        cin.ignore();
                                        getline(cin, plat_Fitria);
                                        NodeBusFitria* bus_Fitria = bst.searchBus_Fitria(plat_Fitria);
                                        
                                        if (bus_Fitria == nullptr) {
                                            cout << "Bus tidak ditemukan.\n";
                                        } else {
                                            cout << "\nData Bus Ditemukan:\n";
                                            cout << "Plat: " << bus_Fitria->platNomor_Fitria << endl;
                                            cout << "Rute: " << bus_Fitria->rute_Fitria << endl;
                                            cout << "Kapasitas: " << bus_Fitria->kapasitas_Fitria << endl;
                                            cout << "Status: " << bus_Fitria->status_Fitria << endl;
                                            
                                            string newRute_Fitria, newStatus_Fitria;
                                            int newKapasitas_Fitria;
                                            cout << "\nMasukkan rute baru: ";
                                            cin.ignore();
                                            getline(cin, newRute_Fitria);
                                            cout << "Masukkan kapasitas baru: ";
                                            cin >> newKapasitas_Fitria;
                                            cout << "Masukkan status baru: ";
                                            cin.ignore();
                                            getline(cin, newStatus_Fitria);
                                            
                                            bst.updateBus_Fitria(plat_Fitria, newRute_Fitria, newKapasitas_Fitria, newStatus_Fitria);
                                        }
                                        pause_Fitria();
                                        break;
                                    }
                                    case 4: { // Ubah status
                                        string plat_Fitria, newStatus_Fitria;
                                        cout << "Masukkan plat nomor: ";
                                        cin.ignore();
                                        getline(cin, plat_Fitria);
                                        NodeBusFitria* bus_Fitria = bst.searchBus_Fitria(plat_Fitria);
                                        
                                        if (bus_Fitria == nullptr) {
                                            cout << "Bus tidak ditemukan.\n";
                                        } else {
                                            cout << "Status saat ini: " << bus_Fitria->status_Fitria << endl;
                                            cout << "Masukkan status baru (Beroperasi/Perbaikan/Cadangan): ";
                                            cin.ignore();
                                            getline(cin, newStatus_Fitria);
                                            bus_Fitria->status_Fitria = newStatus_Fitria;
                                            cout << "Status berhasil diubah.\n";
                                        }
                                        pause_Fitria();
                                        break;
                                    }
                                    case 5: { // Tampilkan semua
                                        bst.displayBusStats_Fitria();
                                        bst.displayAllBus_Fitria();
                                        pause_Fitria();
                                        break;
                                    }
                                    case 6: { // In-order traversal
                                        bst.displayInOrder_Fitria();
                                        pause_Fitria();
                                        break;
                                    }
                                }
                            } while (busChoice_Fitria != 7);
                            break;
                        }
                        
                        case 3: { // Kelola Jadwal
                            int jadwalAdminChoice_Fitria;
                            do {
                                clearScreen_Fitria();
                                displayJadwalAdminMenu_Fitria();
                                cin >> jadwalAdminChoice_Fitria;
                                
                                switch (jadwalAdminChoice_Fitria) {
                                    case 1: { // Cari jadwal
                                        int searchType_Fitria;
                                        cout << "\nCari berdasarkan:\n";
                                        cout << "1. Bus\n2. Rute\n3. Waktu\n";
                                        cout << "Pilihan (1/2/3): ";
                                        cin >> searchType_Fitria;
                                        
                                        if (searchType_Fitria == 1) {
                                            string busID_Fitria;
                                            cout << "\nMasukkan plat bus: ";
                                            cin.ignore();
                                            getline(cin, busID_Fitria);
                                            vector<NodeJadwalFitria*> results_Fitria = jadwal.searchByBus_Fitria(busID_Fitria);
                                            
                                            if (results_Fitria.empty()) {
                                                cout << "Tidak ditemukan.\n";
                                            } else {
                                                cout << "\nHasil Pencarian:\n";
                                                for (auto jadwal_Fitria : results_Fitria) {
                                                    cout << "Bus: " << jadwal_Fitria->busID_Fitria
                                                         << " | Rute: " << jadwal_Fitria->rute_Fitria
                                                         << " | Waktu: " << jadwal_Fitria->waktu_Fitria
                                                         << " | Durasi: " << jadwal_Fitria->durasi_Fitria << " menit\n";
                                                }
                                            }
                                        } else if (searchType_Fitria == 2) {
                                            string rute_Fitria;
                                            cout << "\nMasukkan rute: ";
                                            cin.ignore();
                                            getline(cin, rute_Fitria);
                                            vector<NodeJadwalFitria*> results_Fitria = jadwal.searchByRute_Fitria(rute_Fitria);
                                            
                                            if (results_Fitria.empty()) {
                                                cout << "Tidak ditemukan.\n";
                                            } else {
                                                cout << "\nHasil Pencarian:\n";
                                                for (auto jadwal_Fitria : results_Fitria) {
                                                    cout << "Bus: " << jadwal_Fitria->busID_Fitria
                                                         << " | Rute: " << jadwal_Fitria->rute_Fitria
                                                         << " | Waktu: " << jadwal_Fitria->waktu_Fitria
                                                         << " | Durasi: " << jadwal_Fitria->durasi_Fitria << " menit\n";
                                                }
                                            }
                                        } else if (searchType_Fitria == 3) {
                                            string waktu_Fitria;
                                            cout << "\nMasukkan waktu (HH:MM): ";
                                            cin >> waktu_Fitria;
                                            vector<NodeJadwalFitria*> results_Fitria = jadwal.searchByWaktu_Fitria(waktu_Fitria);
                                            
                                            if (results_Fitria.empty()) {
                                                cout << "Tidak ditemukan.\n";
                                            } else {
                                                cout << "\nHasil Pencarian:\n";
                                                for (auto jadwal_Fitria : results_Fitria) {
                                                    cout << "Bus: " << jadwal_Fitria->busID_Fitria
                                                         << " | Rute: " << jadwal_Fitria->rute_Fitria
                                                         << " | Waktu: " << jadwal_Fitria->waktu_Fitria
                                                         << " | Durasi: " << jadwal_Fitria->durasi_Fitria << " menit\n";
                                                }
                                            }
                                        }
                                        pause_Fitria();
                                        break;
                                    }
                                    case 2: { // Buat jadwal
                                        string busID_Fitria, rute_Fitria, waktu_Fitria;
                                        int durasi_Fitria;
                                        cout << "Masukkan plat bus: ";
                                        cin.ignore();
                                        getline(cin, busID_Fitria);
                                        cout << "Masukkan rute: ";
                                        cin.ignore();
                                        getline(cin, rute_Fitria);
                                        cout << "Masukkan waktu (HH:MM): ";
                                        cin >> waktu_Fitria;
                                        cout << "Masukkan durasi (menit): ";
                                        cin >> durasi_Fitria;
                                        jadwal.insertJadwal_Fitria(busID_Fitria, rute_Fitria, waktu_Fitria, durasi_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 3: { // Hapus jadwal
                                        string busID_Fitria, waktu_Fitria;
                                        cout << "Masukkan plat bus: ";
                                        cin.ignore();
                                        getline(cin, busID_Fitria);
                                        cout << "Masukkan waktu (HH:MM): ";
                                        cin >> waktu_Fitria;
                                        jadwal.deleteJadwal_Fitria(busID_Fitria, waktu_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 4: { // Cari + Edit jadwal (hapus + buat baru)
                                        string busID_Fitria, waktuLama_Fitria, waktuBaru_Fitria, rute_Fitria;
                                        int durasi_Fitria;
                                        cout << "Masukkan plat bus: ";
                                        cin.ignore();
                                        getline(cin, busID_Fitria);
                                        cout << "Masukkan waktu lama (HH:MM): ";
                                        cin >> waktuLama_Fitria;
                                        cout << "Masukkan waktu baru (HH:MM): ";
                                        cin >> waktuBaru_Fitria;
                                        cout << "Masukkan rute baru: ";
                                        cin.ignore();
                                        getline(cin, rute_Fitria);
                                        cout << "Masukkan durasi baru (menit): ";
                                        cin >> durasi_Fitria;
                                        
                                        // Hapus jadwal lama
                                        jadwal.deleteJadwal_Fitria(busID_Fitria, waktuLama_Fitria);
                                        // Buat jadwal baru
                                        jadwal.insertJadwal_Fitria(busID_Fitria, rute_Fitria, waktuBaru_Fitria, durasi_Fitria);
                                        pause_Fitria();
                                        break;
                                    }
                                    case 5: { // Tampilkan semua
                                        jadwal.displayAllJadwal_Fitria();
                                        pause_Fitria();
                                        break;
                                    }
                                }
                            } while (jadwalAdminChoice_Fitria != 6);
                            break;
                        }
                    }
                } while (adminChoice_Fitria != 4);
                break;
            }
            
            case 5: { // Keluar
                clearScreen_Fitria();
                cout << "\n=================================================\n";
                cout << "     TERIMA KASIH TELAH MENGGUNAKAN SISTEM\n";
                cout << "     PENGELOLAAN BUS KOTA - FITRIA LM\n";
                cout << "=================================================\n";
                running_Fitria = false;
                break;
            }
            
            default:
                cout << "Pilihan tidak valid.\n";
                pause_Fitria();
                break;
        }
    }
    
    return 0;
}