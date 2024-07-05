document.addEventListener("DOMContentLoaded", () => {
    // Example of an alert on page load
    alert("Welcome to my personal website!");

    // Example of a button click event
    document.querySelectorAll('button.custom-button').forEach(button => {
        button.addEventListener('click', () => {
            alert("Button clicked!");
        });
    });
});
