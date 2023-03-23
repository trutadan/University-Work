const list1 = document.getElementById("list1");
const list2 = document.getElementById("list2");

list1.addEventListener("dblclick", () => {
  const selectedOption = list1.options[list1.selectedIndex];
  if (selectedOption) {
    list2.appendChild(selectedOption);
  }
});

list2.addEventListener("dblclick", () => {
  const selectedOption = list2.options[list2.selectedIndex];
  if (selectedOption) {
    list1.appendChild(selectedOption);
  }
});
