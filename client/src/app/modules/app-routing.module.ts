import { HttpClientModule } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { DashboardComponent } from '../components/dashboard/dashboard.component';
import { DatabasePageComponent } from '../components/database-page/database-page.component';
import { MapPageComponent } from '../components/map-page/map-page.component';
import { TextEditorPageComponent } from '../components/text-editor-page/text-editor-page.component';

const routes: Routes = [
  {path: 'dashboard', component: DashboardComponent},
  {path: 'maps', component: MapPageComponent},
  {path: 'database', component: DatabasePageComponent},
  {path: 'text-editor', component: TextEditorPageComponent},
  { path: '',   redirectTo: '/dashboard', pathMatch: 'full' },
];

@NgModule({
  imports: [RouterModule.forRoot(routes), HttpClientModule],
  exports: [RouterModule]
})
export class AppRoutingModule { }
