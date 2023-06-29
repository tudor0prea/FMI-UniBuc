using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Microsoft.AspNetCore.Authorization;
using Microsoft.EntityFrameworkCore.Metadata.Internal;
using Microsoft.AspNetCore.Identity;
using PROIECT.Data;
using PROIECT.Models;
using System.Transactions;
using System.Text.RegularExpressions;

namespace PROIECT.Controllers
{
    [Authorize] // doar cei inregistrati sa vada articolele 
    public class ArticlesController : Controller
    {
        //In final, in cadrul fiecarui Controller se realizeaza conexiunea cu baza de date astfel:

        private readonly ApplicationDbContext db;
        private readonly UserManager<ApplicationUser> _userManager;
        private readonly RoleManager<IdentityRole> _roleManager;
        public ArticlesController(ApplicationDbContext context,
        UserManager<ApplicationUser> userManager,
        RoleManager<IdentityRole> roleManager
        )
        {
            db = context;
            _userManager = userManager;
            _roleManager = roleManager;
        }


        [Authorize(Roles = "User,Editor,Admin")] // doar ei pot sa vada 
        //Pentru fiecare utilizator se afiseaza si utilizatorul care a postat articolul
        public IActionResult Index()
        {
            //
            int _perPage = 2; // 5 pe pagina 

            var articles = db.Articles.Include("Domain").Include("User") // initial ne uitam la toate articolele
                                                        .Where(art=>art.ShowInDatabase == true)                                            
                                                        .OrderBy(a => a.Date);

            ViewBag.Domains = GetAllDomains();

            //ViewBag.Domains = GetAllDomains().Select(x =>
            //                      new SelectListItem()
            //                      {
            //                          Text = x.ToString()
            //                      }); // selectam domeniile pentru dropDown

            int chosenDomain = -1;

            //ALEGEREA DOMENIULUI 
            if (Convert.ToString(HttpContext.Request.Query["domain"]) != null)
            {
                chosenDomain = Convert.ToInt16(HttpContext.Request.Query["domain"]);
               
                articles = (IOrderedQueryable<Article>)db.Articles.Include("Domain").Include("User")
                                                            .Where(art => art.ShowInDatabase == true)
                                                            .Where(art=>art.DomainId == chosenDomain);
            }

            var search = "";

            // MOTOR DE CAUTARE
            if (Convert.ToString(HttpContext.Request.Query["search"]) != null)
            {
                // eliminam spatiile libere
                search = Convert.ToString(HttpContext.Request.Query["search"]).Trim();

                List<int> articleIds = db.Articles.Where(
                 (at => at.Title.Contains(search)
                 || at.Content.Contains(search) && at.ShowInDatabase == true)
                 ).Select(a => a.Id).ToList();

                // Lista articolelor care contin cuvantul cautat
                // in articol -> Title si Content
                articles = db.Articles.Where(article => articleIds.Contains(article.Id) && article.ShowInDatabase == true)
                         .Include("Domain")
                         .Include("User")
                         .OrderBy(a => a.Date);

            }

            ViewBag.SearchString = search;

            int totalItems = articles.Count(); // Fiind un numar variabil de articole, verificam de fiecare data 
           
            // Se preia pagina curenta din View-ul asociat
            // Numarul paginii este valoarea parametrului page din ruta
            // /Articles/Index?page=valoare
            var currentPage = Convert.ToInt32(HttpContext.Request.Query["page"]);

            // Pentru prima pagina offsetul o sa fie zero
            // Pentru pagina 2 o sa fie 3
            // Asadar offsetul este egal cu numarul de articole
            //care au fost deja afisate pe paginile anterioare
            var offset = 0;
            // Se calculeaza offsetul in functie de numarul paginii la care suntem
            if (!currentPage.Equals(0))
            {
                offset = (currentPage - 1) * _perPage;
            }

            // Se preiau articolele corespunzatoare pentru
            //fiecare pagina la care ne aflam
            // in functie de offset
            var paginatedArticles = articles.Skip(offset).Take(_perPage);

            // Preluam numarul ultimei pagini
            ViewBag.lastPage = Math.Ceiling((float)totalItems / (float)_perPage);

            // Trimitem articolele cu ajutorul unui ViewBag
            //catre View-ul corespunzator
            ViewBag.Articles = paginatedArticles;

            if (TempData.ContainsKey("message"))
            {
                ViewBag.Msg = TempData["message"];
            }


            if (search != "")
            {
                ViewBag.PaginationBaseUrl = "/Articles/Index/?search="
               + search + "&page";
            }
            else
            {
                ViewBag.PaginationBaseUrl = "/Articles/Index/?page";
            }


            return View();
        }


        [Authorize(Roles = "User,Editor,Admin")]
        public IActionResult Show(int id)
        {
            Article article = db.Articles.Include("Domain").Include("User")
                               .Where(art => art.Id == id && art.ShowInDatabase == true) // posibil sa nu fie nevoie de showInDatabase
                               .First();

            setAccesRights();

            //Pentru a putea trimite Modelul catre View si pentru a putea fi folosit
            //este nevoie de article ca parametru pentru View

            return View(article);
        }

        private void setAccesRights()
        {
            ViewBag.AfisareButoane = false;

            if (User.IsInRole("Editor"))
            {
                ViewBag.AfisareButoane = true;
            }

            ViewBag.UserCurent = _userManager.GetUserId(User);

            ViewBag.EsteAdmin = User.IsInRole("Admin");
        }

        [Authorize(Roles = "Editor,Admin")]
        public IActionResult New()
        {
            Article article = new Article();

            article.Dom = GetAllDomains();

            return View(article);
        }


        // Se adauga articolul in baza de date
        [HttpPost]
        [Authorize(Roles = "Editor,Admin")]
        public IActionResult New(Article article)
        {

            article.ShowInDatabase = true; // sa il afisam in baza de date
            article.Date = DateTime.Now;
            article.UserID = _userManager.GetUserId(User);

            if (ModelState.IsValid)
            {
                article.PreviousArticles = new List<Article>(); // initializez lista de articole pentru versiunile anterioare. Momentan e goala, asta fiind prima VERSIUNE
                db.Articles.Add(article);
                db.SaveChanges();

                //Helperul TempData – poate seta o valoare care va fi disponibila intr-un request subsecvent
                TempData["message"] = "Articolul a fost adaugat";
                return RedirectToAction("Index");
            }
            else
            {
                article.Dom = GetAllDomains();
                return View(article);
            }
        }


        [Authorize(Roles = "Editor,Admin")]
        public IActionResult Edit(int id)
        {
            Article article = db.Articles.Include("Domain")
                                         .Where(art => art.Id == id)
                                         .First();
            article.Dom = GetAllDomains();
            if (article.UserID == _userManager.GetUserId(User) || User.IsInRole("Admin"))
                return View(article);

            else
            {
                TempData["message"] = "Nu aveti drepuri suficiente";
                return RedirectToAction("Index");
            }
        }


        [HttpPost]
        [Authorize(Roles = "Editor,Admin")]
        public IActionResult Edit(int id, Article requestArticle)
        {
            Article article = db.Articles.Include("PreviousArticles")
                                         .Where(art => art.Id == id)
                                         .First();

            if (ModelState.IsValid)
            {
                if (article.UserID == _userManager.GetUserId(User) || User.IsInRole("Admin"))
                {

                    // adaug articolul inainte sa fie modificat ca fiind variant ANTERIOARA 
                    //versiunea anterioara deoarece au acc id, solutia e sa creez Articol nou dar fara sa l bag in baza de date probabil
                    Article aux = new Article();
                    aux.Title = article.Title;
                    aux.Content = article.Content;
                    aux.DomainId = article.DomainId;
                    aux.Date = DateTime.Now;
                    aux.UserID = _userManager.GetUserId(User);
                    aux.ShowInDatabase = false;
                    article.PreviousArticles.Add(aux);

                    article.Title = requestArticle.Title;
                    article.Content = requestArticle.Content;
                    article.DomainId = requestArticle.DomainId;
                    TempData["message"] = "Articolul a fost modificat";
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                else
                {
                    TempData["message"] = "Nu aveti drepuri suficiente";
                    return RedirectToAction("Index");
                }
            }
            else
            {
                requestArticle.Dom = GetAllDomains();
                return View(requestArticle);
            }
        }


        // Se sterge un articol din baza de date 
        [HttpPost]
        [Authorize(Roles = "Editor,Admin")]
        public ActionResult Delete(int id)
        {
            Article article = db.Articles.Include("PreviousArticles")
                                         .Where(art => art.Id == id)
                                         .First();
            if (article.UserID == _userManager.GetUserId(User) || User.IsInRole("Admin"))
            {
                db.Articles.Remove(article);
                TempData["message"] = "Articolul a fost sters";
                db.SaveChanges();
                return RedirectToAction("Index");
            }
            else
            {
                TempData["message"] = "Nu aveti drepuri suficiente";
                return RedirectToAction("Index");
            }
        }

        [HttpPost]
        [Authorize(Roles = "Admin")]
        public IActionResult Undo(int id)
        {
            Article article = db.Articles.Include("PreviousArticles")
                                         .Where(art => art.Id == id)
                                         .First();


            if (article.PreviousArticles.Count > 0)
            {

                if (User.IsInRole("Admin")) // doar daca e admin poate reveni la forma initala 
                {
                    Article previous = db.Articles.Find(article.PreviousArticles.Last().Id);

                    article.Title = previous.Title;
                    article.Content = previous.Content;
                    article.DomainId = previous.DomainId;
                    article.PreviousArticles.Remove(article.PreviousArticles.Last());
                    TempData["message"] = "Articolul a fost adus la versiunea anteriara";
                    db.Articles.Remove(previous);
                    db.SaveChanges();
                    return RedirectToAction("Index");
                }
                else
                {
                    TempData["message"] = "Nu aveti drepuri suficiente";
                    return RedirectToAction("Index");
                }
            }
            else
            {
                if (article.PreviousArticles.Count == 0)
                    TempData["message"] = "Articolul nu are o versiune anterioara";

                return RedirectToAction("Index");
            }
        }

        public IEnumerable<SelectListItem> GetAllDomains()
        {
            // generam o lista de tipul SelectListItem fara elemente
            var selectList = new List<SelectListItem>();
            // extragem toate domeniile din baza de date
            var domains = from dom in db.Domains
                          select dom;
            // iteram prin categorii
            foreach (var domain in domains)
            {
                // adaugam in lista elementele necesare pentru dropdown
                // id-ul domeniului si denumirea acestuia
                selectList.Add(new SelectListItem
                {
                    Value = domain.Id.ToString(),
                    Text = domain.DomainName.ToString()
                });
            }
            /* Sau se poate implementa astfel:
            *
            foreach (var domain in domains)
            {
            var listItem = new SelectListItem();
           listItem.Value = domain.Id.ToString();
           listItem.Text = domain.DomainName.ToString();
            selectList.Add(listItem);
            }*/

            // returnam lista de domenii
            return selectList;
        }
    }

}

