#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct {
    int page_number;
    uint8_t counter;
} page_frame_t;

typedef struct {
    uint32_t hits;
    uint32_t misses;
} pager_perf_ratio_t;

typedef struct {
    page_frame_t ** frames;
    uint32_t page_amount;
    pager_perf_ratio_t perf_ratio;
} ageing_pager_t;

void tick(const ageing_pager_t * pager) {
    for (int i = 0; i < pager->page_amount; i++) {
        if (pager->frames[i]) {
            pager->frames[i]->counter >>= 1u;
        }
    }
}

page_frame_t * find_frame_by_number(ageing_pager_t * pager, int page_number) {
    for (int i = 0; i < pager->page_amount; i++) {
        if (pager->frames[i] && page_number == pager->frames[i]->page_number) {
            return pager->frames[i];
        }
    }
    return NULL;
}

page_frame_t * insert_frame(ageing_pager_t * pager, int page_number) {
    page_frame_t ** oldest = &pager->frames[0];
    for (int i = 1; i < pager->page_amount; i++) {
        if (!pager->frames[i] || (*oldest && pager->frames[i]->counter < (*oldest)->counter)) {
            oldest = &pager->frames[i];
        }
    }
    
    if (*oldest) {
        free(*oldest);
    }
    *oldest = malloc(sizeof(page_frame_t));
    (*oldest)->page_number = page_number;
    (*oldest)->counter = (uint8_t) (1 << 7u);

    return *oldest;
}

void reference(ageing_pager_t * pager, int page_number) {
    page_frame_t * frame = find_frame_by_number(pager, page_number);
    if (frame) {
        pager->perf_ratio.hits++;
        frame->counter |= (uint8_t) (1 << 7u);
    } else {
        pager->perf_ratio.misses++;
        insert_frame(pager, page_number);
    }
}

ageing_pager_t * create_ageing_pager(int page_amount) {
    ageing_pager_t * pager = malloc(sizeof(ageing_pager_t));

    pager->page_amount = page_amount;
    pager->frames = malloc(page_amount * sizeof(page_frame_t*));
    memset(pager->frames, 0, page_amount * sizeof(page_frame_t*));
    pager->perf_ratio.hits = 0;
    pager->perf_ratio.misses = 0;

    return pager;
}

void print_perf_ratio(const ageing_pager_t * pager) {
    pager_perf_ratio_t p = pager->perf_ratio;
    uint32_t total = p.hits + p.misses;
    printf("hit: %d (%f%%), miss: %d (%f%%), hit/miss: %f", p.hits, (float) p.hits / total * 100, p.misses, (float) p.misses / total * 100, (float) p.hits / p.misses);
}

int main() {
    uint32_t page_amount;
    scanf("%u", &page_amount);
    ageing_pager_t * pager = create_ageing_pager(page_amount);
    int page_reference;
    while (scanf("%d", &page_reference) != 0) {
        if (page_reference == -1) break;  // TODO: remove
        if (page_reference == 0) continue;
        tick(pager);
        reference(pager, page_reference);
    }
    print_perf_ratio(pager);
}