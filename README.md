 Social Network Simulation: Red-Black Tree & Graph Analysis
Bu proje, C dilinde veri yapılarını ve algoritmaları uçtan uca kullanarak geliştirilmiş bir sosyal ağ arka plan simülasyonudur. Sistem, kullanıcı verilerini Red-Black Tree ile yönetirken, sosyal ilişkileri Graph teorisi ile analiz eder.

 Projenin Amacı:
Projenin temel amacı, büyük veri setlerinde hızlı arama yapılmasını sağlayan dengeli ağaç yapıları ile (Red-Black Tree) ilişkisel verilerin (Graph) bir arada nasıl verimli kullanılabileceğini göstermektir.
 
 Teknik Özellikler:
Hızlı Kullanıcı Yönetimi: Kullanıcılar benzersiz ID'leri ile Red-Black Tree yapısında saklanır. Bu sayede ekleme ve arama işlemleri en kötü durumda bile $O(\log n)$ karmaşıklığında gerçekleşir.

Sosyal İlişki Analizi: Kullanıcılar arasındaki arkadaşlık bağları bir Adjacency List (Komşuluk Listesi) yapısında tutulur.

Topluluk Tespiti: DFS (Depth-First Search) algoritması kullanılarak ağ üzerindeki izole topluluklar (birbirine bağlı gruplar) tespit edilir.

Etki Alanı (Influence) Hesaplama: Bir kullanıcının sosyal ağda kaç kişiye erişebildiği özyinelemeli (recursive) algoritmalarla hesaplanır.

Kullanılan Teknolojiler & Algoritmalar

Dil: C

Veri Yapıları: Red-Black Tree (Self-balancing), Graph, Linked List, Structs.

Önemli Fonksiyonlar:
fixInsert: Ağaca yeni veri eklendiğinde renk dengesini korur.
dfs: Sosyal ağ üzerinde derinlemesine arama yapar.
findCommonFriends: İki kullanıcı arasındaki ortak arkadaşları listeler.
