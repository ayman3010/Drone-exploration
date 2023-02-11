import { Component } from '@angular/core';

@Component({
  selector: 'app-sidenav',
  templateUrl: './sidenav.component.html',
  styleUrls: ['./sidenav.component.scss']
})
export class SidenavComponent {

  navData = [
    {
      routerLink: 'dashboard',
      icon: 'fa-solid fa-helicopter',
    },
    {
      routerLink: 'maps',
      icon: 'fa-solid fa-map-location-dot',
    },
    {
      routerLink: 'database',
      icon: 'fa-solid fa-database',
    },
    {
      routerLink: 'text-editor',
      icon: 'fa-solid fa-file-lines',
    },
  ];
}
