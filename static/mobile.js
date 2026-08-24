document.addEventListener('DOMContentLoaded', () => {
  const menuBtn = document.querySelector('.mobile-menu-btn');
  const navLinks = document.querySelector('.nav-links');

  menuBtn.addEventListener('click', () => {
    menuBtn.classList.toggle('is-active');
    navLinks.classList.toggle('is-open');
    document.documentElement.classList.toggle('menu-open');
    document.body.classList.toggle('menu-open');
  });

  navLinks.querySelectorAll('a').forEach(link => {
    link.addEventListener('click', () => {
      menuBtn.classList.remove('is-active');
      navLinks.classList.remove('is-open');
      document.documentElement.classList.remove('menu-open');
      document.body.classList.remove('menu-open');
    });
  });
});
