    // Nama : Muhammad Raihan Abubakar
    // Nama fitur : paddle (pakai linked list)
    // Deskripsi : paddle berfungsi untuk memantulkan dan mengarahkan bola agar bisa menghancurkan block

    #ifndef PADDLE_H
    #define PADDLE_H

    #include <raylib.h>

    #define PADDLE_WIDTH 100 // lebar paddle
    #define PADDLE_HEIGHT 20 // tinggi paddle 
    #define PADDLE_SPEED 8 // kecepatan paddle 

    typedef struct Paddle {
        Rectangle rect;        // posisi paddle 
        Vector2 speed;         // kecepatan paddle
        struct Paddle* next;   // pointer ke paddle berikutnya
    } Paddle;

    Paddle* CreatePaddle(float x, float y); // buat paddle baru
    void AddPaddle(Paddle** head, float x, float y); // tambahkan paddle ke list
    void InitPaddles(Paddle** head); // inisiasi paddle
    void UpdatePaddles(Paddle* head); // update semua paddle
    void DrawPaddles(Paddle* head); // gambar semua paddle
    void FreePaddles(Paddle* head); // hapus semua paddle dari memori

    #endif // PADDLE_H
