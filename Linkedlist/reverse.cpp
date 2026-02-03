class Node {
    constructor(new_data) {
        this.data = new_data;
        this.next = null;
    }
}
 
function reverseList(head) {
    if (head === null || head.next === null)
        return head;
 
    // reverse the rest of linked list
    let rest = reverseList(head.next);
 
    // make the current head as last node of
    // remaining linked list
    head.next.next = head;
 
    // update next of current head to null
    head.next = null;
 
    return rest;
}
 
function printList(node) {
    let result = [];
    while (node !== null) {
        result.push(node.data);
        node = node.next;
    }
    console.log(result.join(" -> "));
}
 
// Driver code
let head = new Node(1);
head.next = new Node(2);
head.next.next = new Node(3);
head.next.next.next = new Node(4);
head.next.next.next.next = new Node(5);
 
head = reverseList(head);
printList(head);