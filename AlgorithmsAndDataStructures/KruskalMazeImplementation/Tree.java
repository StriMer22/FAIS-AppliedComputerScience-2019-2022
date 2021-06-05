package KruskalMaze;

class Tree {
    private Tree parent = null;

    public Tree() {

    }

    public Tree root() {
        return parent != null ? parent.root() : this;
    }

    public boolean connected(Tree tree) {
        return this.root() == tree.root();
    }

    public void connect(Tree tree) {
        tree.root().setParent(this);
    }

    public void setParent(Tree parent) {
        this.parent = parent;
    }
}
