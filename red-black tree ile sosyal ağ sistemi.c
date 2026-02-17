
                z = grand;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rightRotate(root, z);
                }
                z->parent->color = BLACK;
                grand->color = RED;
                leftRotate(root, grand);
            }
        }
    }
    (*root)->color = BLACK;
}

// Kullanici Red-Black Tree icerisine ekle
void insertUser(User* user) {
    RBNode* z = createRBNode(user);
    RBNode* y = NULL;
    RBNode* x = root;
    while (x) {
        y = x;
        if (user->id < x->user->id)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (!y)
        root = z;
    else if (user->id < y->user->id)
        y->left = z;
    else
        y->right = z;

    fixInsert(&root, z);
}

// ID'ye gore kullanici ara
User* searchUser(RBNode* node, int id) {
    if (!node) return NULL;
    if (id == node->user->id) return node->user;
    if (id < node->user->id) return searchUser(node->left, id);
    return searchUser(node->right, id);
}

// ---------------- Arkadaslik ve Kullanici Islemleri ----------------

// Yeni kullanici olustur
User* createUser(int id) {
    User* user = (User*)malloc(sizeof(User));
    user->id = id;
    user->friends = NULL;
    user->visited = 0;
    insertUser(user);
    return user;
}

// Iki kullaniciyi arkadas yap
void addFriend(User* a, User* b) {
    FriendNode* newNode = (FriendNode*)malloc(sizeof(FriendNode));
    newNode->user = b;
    newNode->next = a->friends;
    a->friends = newNode;
}

// ---------------- Analiz Fonksiyonlari ----------------

// Tum kullanicilarda ziyaret bilgisi sifirla
void resetVisited(RBNode* node) {
    if (!node) return;
    node->user->visited = 0;
    resetVisited(node->left);
    resetVisited(node->right);
}

// Derinlik oncelemeli arama (DFS)
void dfs(User* user, int depth) {
    if (!user || user->visited || depth < 0) return;
    user->visited = 1;
    printf("Kullanici ID: %d (mesafe: %d)\n", user->id, depth);
    FriendNode* f = user->friends;
    while (f) {
        dfs(f->user, depth - 1);
        f = f->next;
    }
}

// Ortak arkadaslari bul
void findCommonFriends(User* a, User* b) {
    printf("\nOrtak arkadaslar:\n");
    FriendNode* fa = a->friends;
    while (fa) {
        FriendNode* fb = b->friends;
        while (fb) {
            if (fa->user == fb->user)
                printf("ID: %d\n", fa->user->id);
            fb = fb->next;
        }
        fa = fa->next;
    }
}

// Erişilebilen kullanici sayisini say
int countReachable(User* user) {
    if (!user || user->visited) return 0;
    user->visited = 1;
    int count = 1;
    FriendNode* f = user->friends;
    while (f) {
        count += countReachable(f->user);
        f = f->next;
    }
    return count;
}

// Topluluklari tespit et
void detectCommunities(RBNode* node) {
    if (!node) return;
    detectCommunities(node->left);
    if (!node->user->visited) {
        printf("\nTopluluk:\n");
        int size = countReachable(node->user);
        printf("Boyut: %d\n", size);
    }
    detectCommunities(node->right);
}

// Etki alanini hesapla
int calculateInfluence(User* user) {
    resetVisited(root);
    return countReachable(user) - 1;
}

// ---------------- Ana Fonksiyon ----------------

int main() {
    // Ornek kullanicilar
    createUser(101);
    createUser(102);
    createUser(103);
    createUser(104);
    createUser(105);

    // Ornek arkadasliklar
    User* u101 = searchUser(root, 101);
    User* u102 = searchUser(root, 102);
    User* u103 = searchUser(root, 103);
    User* u104 = searchUser(root, 104);
    User* u105 = searchUser(root, 105);

    addFriend(u101, u102); addFriend(u102, u101);
    addFriend(u101, u103); addFriend(u103, u101);
    addFriend(u102, u104); addFriend(u104, u102);
    addFriend(u103, u104); addFriend(u104, u103);
    addFriend(u104, u105); addFriend(u105, u104);

    // DFS: 101'den 2 adim uzakliktakiler
    printf("\n[DFS] 101'den 2 mesafe uzakliktakiler:\n");
    resetVisited(root);
    dfs(u101, 2);

    // Ortak arkadaslar
    findCommonFriends(u102, u103);

    // Topluluk tespiti
    resetVisited(root);
    detectCommunities(root);

    // Etki alani hesaplama
    int influence = calculateInfluence(u101);
    printf("\n101 numarali kullanicinin etki alani: %d kisi\n", influence);

    return 0;
}
