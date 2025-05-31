// Nama Pembuat: Nezya Zulfa Fauziah
// Nama Fitur: Level
// Deskripsi: Fitur level ini mengatur jenis dan ketahanan blok dalam game Break Bricks berdasarkan level yang dipilih.
// Level 1 hanya memiliki blok kuning (HP 1), level 2 menambahkan blok oranye (HP 2), dan level 3 menambahkan blok ungu (HP 3).
// Blok-blok diatur dalam grid dan dimasukkan secara dinamis ke linked list.
// Sistem ini memungkinkan variasi tantangan di setiap level dan dapat di-reset saat level berubah.

#ifndef LINKEDLIST_LEVEL_H
#define LINKEDLIST_LEVEL_H

#include "block.h"

void InitLevelBlocks(LinkedList *blockList, int level);
void SetLevel(LinkedList *blockList, int level);

#endif
