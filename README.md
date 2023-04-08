# Protokoll: AVL-Baumprüfer

## Rekursive Funktionen

### insert
Beschreibung: Fügt einen neuen Knoten mit einem Schlüsselwert in den Baum ein. Die Funktion sucht rekursiv den geeigneten Platz für den neuen Knoten, abhängig von seinem Wert.
Aufwandsabschätzung: O(h), wobei h die Höhe des Baums ist.

### countNodes
Beschreibung: Zählt rekursiv die Anzahl der Knoten im Baum.
Aufwandsabschätzung: O(n), wobei n die Anzahl der Knoten im Baum ist.

### height
Beschreibung: Bestimmt rekursiv die Höhe des Baums.
Aufwandsabschätzung: O(n), wobei n die Anzahl der Knoten im Baum ist.

### calculateBalanceFactors
Beschreibung: Berechnet rekursiv den Balancefaktor für jeden Knoten im Baum.
Aufwandsabschätzung: O(n), wobei n die Anzahl der Knoten im Baum ist.

### isAVL
Beschreibung: Prüft rekursiv, ob der gegebene Baum ein AVL-Baum ist oder nicht, indem überprüft wird, ob der Balancefaktor jedes Knotens innerhalb des zulässigen Bereichs (-1, 0, 1) liegt.
Aufwandsabschätzung: O(n), wobei n die Anzahl der Knoten im Baum ist.

### printBalanceFactors
Beschreibung: Druckt rekursiv die Balancefaktoren aller Knoten im Baum.
Aufwandsabschätzung: O(n), wobei n die Anzahl der Knoten im Baum ist.

### statistics
Beschreibung: Sammelt rekursiv Statistiken wie den minimalen, maximalen und durchschnittlichen Wert der Knoten im Baum.
Aufwandsabschätzung: O(n), wobei n die Anzahl der Knoten im Baum ist.

### isSubtree
Beschreibung: Überprüft rekursiv, ob ein gegebener Baum ein Unterbaum eines anderen Baums ist.
Aufwandsabschätzung: O(m * n), wobei m und n die Anzahl der Knoten in den beiden Bäumen sind.

### isSameStructure
Beschreibung: Vergleicht rekursiv die Struktur zweier Bäume und prüft, ob sie identisch sind.
Aufwandsabschätzung: O(m * n), wobei m und n die Anzahl der Knoten in den beiden Bäumen sind.

### findNodePath
Beschreibung: Findet rekursiv den Pfad zu einem Knoten im Baum mit einem gegebenen Schlüsselwert.
Aufwandsabschätzung: O(h), wobei h die Höhe des Baums ist.

### deleteTree
Beschreibung: Löscht rekursiv alle Knoten im Baum und gibt den Speicher frei.
Aufwandsabschätzung: O(n), wobei n die Anzahl der Knoten im Baum ist.

## Zusammenfassung

Die implementierten rekursiven Funktionen decken alle Aspekte der AVL-Baumprüfung ab, von der Einfügung der Knoten über die Berechnung von Balancefaktoren, die Überprüfung der AVL-Eigenschaft, die Sammlung von Statistiken bis hin zur Überprüfung von Teilbäumen und dem Löschen des Baums. Die meisten Funktionen haben eine lineare Aufwandsabschätzung (O(n)), während einige, wie insert und findNodePath, eine logarithmische Aufwandsabschätzung (O(h)) aufweisen. Die Funktionen isSubtree und isSameStructure haben eine quadratische Aufwandsabschätzung (O(m * n)), was darauf hinweist, dass sie für sehr große Bäume möglicherweise nicht optimal sind.