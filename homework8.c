#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;


int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(listNode** h) {

	// headNode가 NULL x, 할당된 메모리 모두 해제
	if(*h != NULL)
		freeList(*h);

	// headNode에 대한 메모리를 할당하여 리턴
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

int freeList(listNode* h){
    //h->rlink == h 경우, h를 free해준다.
	if(h->rlink == h)
	{
		free(h);
		return 1;
	}
    //p의 주소 h->rlink로
	listNode* p = h->rlink;
    //prev의 주소 NULL
	listNode* prev = NULL;
    //p가 NULL과 h가 아닐때, prev에 p값, p에 rlink값, prev free
	while(p != NULL && p != h) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
    //h free
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");
    // h 가 NULL 인 경우
	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}
    // p = h->rlink
	p = h->rlink;
    
    //p != NULL && p != h 동안, 연결된 노드 계속 이동 출력
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	// 주소 출력
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
    //p != NULL && p != h 동안, 연결된 노드 계속 이동 출력
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}




//list에 key에 대한 노드 추가
int insertLast(listNode* h, int key) {
    
    //h NULL, 리턴
	if (h == NULL) return -1;
    
    //node 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;
    
    // 첫 노드 일때
	if (h->rlink == h)
	{
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	} else { // 그 외인 경우
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}

	return 1;
}


//list의 마지막 노드 삭제
int deleteLast(listNode* h) {
    //비어있는 경우
	if (h->llink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}
    
    //nodetoremove
	listNode* nodetoremove = h->llink;

	//nodetoremove로 h->llink
	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;
    //메모리 취소
	free(nodetoremove);

	return 1;
}



//list 처음에 key에 대한 노드 추가
int insertFirst(listNode* h, int key) {
    //node 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

    //주소 연결
	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;


	return 1;
}


 //list의 첫번째 노드 삭제
int deleteFirst(listNode* h) {
    //h == NULL || h->rlink == h이면
	if (h == NULL || h->rlink == h)
	{
		printf("nothing to delete.\n");
		return 0;
	}
    //nodetoremove를 h->rlink로
	listNode* nodetoremove = h->rlink;

	//주소 빼고연결
	nodetoremove->rlink->llink = h;
	h->rlink = nodetoremove->rlink;
    //메모리 취소
	free(nodetoremove);

	return 1;

}


//리스트의 링크를 역순으로 배치
int invertList(listNode* h) {

    //h->rlink == h || h == NULL인 경우
	if(h->rlink == h || h == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
    //n,trail,middle 선언
	listNode *n = h->rlink;
	listNode *trail = h;
	listNode *middle = h;

	//최종으로 바뀔 링크 유지
	h->llink = h->rlink;
    
    //n != NULL && n != h때까지 위치변환
	while(n != NULL && n != h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}
    
	h->rlink = middle;

	return 0;
}



// 검색, key보다 큰값이 나오는 노드 앞에넣기
int insertNode(listNode* h, int key) {
    
	if(h == NULL) return -1;
    //node 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;
    //h->rlink == h이면 처음에 넣기
	if (h->rlink == h)
	{
		insertFirst(h, key);
		return 1;
	}
    
    //n선언
	listNode* n = h->rlink;

	// key로 크키 비교하여 삽입 위치를 찾기
	while(n != NULL && n != h) {
		if(n->key >= key) {
			// 첫 노드 앞쪽 삽입해야할 경우
			if(n == h->rlink) {
				insertFirst(h, key);
			} else { // 중간이거나 마지막인 경우
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	// 마지막에 삽입
	insertLast(h, key);
	return 0;
}



//list에서 key에 대한 노드 삭제
 
int deleteNode(listNode* h, int key) {
    //아무것도 없으면,
	if (h->rlink == h || h == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
    //n선언
	listNode* n = h->rlink;
    //key로 위치 선택
	while(n != NULL && n != h) {
		if(n->key == key) {
			if(n == h->rlink) { //첫 노드째 노드 인경우
				deleteFirst(h);
			} else if (n->rlink == h){ // 마지막 노드인 경우
				deleteLast(h);
			} else { // 중간인 경우
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}

		n = n->rlink;
	}

	// 찾지 못 하면
	printf("cannot find the node for key = %d\n", key);
	return 0;
}


